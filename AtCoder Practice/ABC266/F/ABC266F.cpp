#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int tar;
bool vis[N], oncyc[N];
vector<int>cyc;
bool dfs(int p, int fa)
{
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		if(vis[j])
		{
			tar = j;
			cyc.push_back(p);
			oncyc[p] = true;
			return true;
		}
		if(dfs(j, p))
		{
			cyc.push_back(p);
			oncyc[p] = true;
			if(tar == p)return false;
			return true;
		}
	}
	return false;
}
int t[N];
void getTop(int p, int fa, int top)
{
	t[p] = top;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa || oncyc[j])continue;
		getTop(j, p, top);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for(int i : cyc)
		getTop(i, 0, i);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(t[u] == t[v])puts("Yes");
		else puts("No");
	}
	return 0;
}