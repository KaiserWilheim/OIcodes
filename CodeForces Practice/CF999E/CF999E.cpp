#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 100010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc;
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
			vis[sta[tt]] = false;
			tt--;
		}
		scc[sta[tt]] = sc;
		vis[sta[tt]] = false;
		tt--;
	}
}
struct Edge
{
	int u, v;
};
Edge edge[M];
int ind[N];
bool tag[N];
void dfs(int p)
{
	tag[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(!tag[e[i]])
			dfs(e[i]);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	int s;
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		edge[i] = { u,v };
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	memset(h, -1, sizeof(h));
	for(int i = 1; i <= m; i++)
	{
		int u = scc[edge[i].u], v = scc[edge[i].v];
		if(u != v)
		{
			ind[v]++;
			add(u, v);
		}
	}
	dfs(scc[s]);
	int ans = 0;
	for(int i = 1; i <= sc; i++)
		if(!tag[i] && !ind[i])ans++;
	printf("%d\n", ans);
	return 0;
}