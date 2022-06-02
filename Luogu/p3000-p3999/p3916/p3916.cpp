#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m, p;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
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
vector<int>v[N];
int res[N], ans[N];
void dfs(int p)
{
	if(ans[p])return;
	ans[p] = res[p];
	for(auto i : v[p])
	{
		dfs(i);
		ans[p] = max(ans[p], ans[i]);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		res[scc[i]] = max(res[scc[i]], i);
		for(int j = h[i]; ~j; j = ne[j])
		{
			int k = e[j];
			if(scc[i] != scc[k])v[scc[i]].push_back(scc[k]);
		}
	}
	for(int i = 1; i <= sc; i++)
		if(!ans[i])dfs(i);
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[scc[i]]);
	return 0;
}
