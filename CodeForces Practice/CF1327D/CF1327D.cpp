#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
vector<int>d[N];
int p[N], c[N];
bool vis[N];
vector<int>cyc[N];
int idx;
void dfs(int s)
{
	idx++;
	cyc[idx].push_back(s);
	vis[s] = true;
	for(int i = p[s]; i != s; i = p[i])
	{
		cyc[idx].push_back(i);
		vis[i] = true;
	}
}
int calc(vector<int>&a)
{
	int n = a.size();
	for(int k : d[n])
	{
		for(int i = 0; i < k; i++)
		{
			bool flag = true;
			for(int j = i; j < n; j += k)
				flag &= (c[a[j]] == c[a[i]]);
			if(flag)return k;
		}
	}
	return n;
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n; i++)
		if(!vis[i])dfs(i);
	int res = 1919810;
	for(int i = 1; i <= idx; i++)
		res = min(res, calc(cyc[i]));
	printf("%d\n", res);
}
int main()
{
	for(int i = 1; i <= 200000; i++)
		for(int j = i; j <= 200000; j += i)
			d[j].push_back(i);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		for(int i = 1; i <= idx; i++)
			cyc[i].clear();
		idx = 0;
		solve();
	}
	return 0;
}