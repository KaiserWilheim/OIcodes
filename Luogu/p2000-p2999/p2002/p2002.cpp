#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
int deg[N];
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1, a, b; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		for(int j = h[i]; ~j; j = ne[j])
		{
			int v = e[j];
			if(scc[i] != scc[v])deg[scc[v]]++;
		}
	}
	int cnt0 = 0;
	for(int i = 1; i <= sc; i++)
		if(!deg[i])cnt0++;
	printf("%d\n", cnt0);
	return 0;
}
