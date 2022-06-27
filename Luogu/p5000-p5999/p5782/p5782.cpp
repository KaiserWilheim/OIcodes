#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, M = 4000010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j);
			low[p] = min(low[p], low[j]);
		}
		else if(vis[j])
		{
			low[p] = min(low[p], dfn[j]);
		}
	}
	if(dfn[p] == low[p])
	{
		++sc;
		while(sta[tt] != p)
		{
			scc[sta[tt]] = sc;
			sz[sc]++;
			vis[sta[tt]] = false;
			tt--;
		}
		scc[sta[tt]] = sc;
		sz[sc]++;
		vis[sta[tt]] = false;
		tt--;
	}
}
#define p(x) (x%2==1)?x+1:x-1
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	memset(h, -1, sizeof(h));
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		add(u, p(v));
		add(v, p(u));
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= 2 * n; i += 2)
	{
		if(scc[i] == scc[i + 1])
		{
			puts("NIE");
			return 0;
		}
	}
	for(int i = 1; i <= 2 * n; i += 2)
		if(scc[i] < scc[i + 1])
			cout << i << endl;
		else
			cout << i + 1 << endl;
	return 0;
}
