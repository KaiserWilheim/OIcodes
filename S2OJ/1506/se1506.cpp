#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 250;
int n, m;
int g[N][N], G[N][N];
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(int i = 1; i <= n; i++)
	{
		if(!g[p][i] || i == p)continue;
		if(!dfn[i])
		{
			tarjan(i);
			low[p] = min(low[p], low[i]);
		}
		else if(vis[i])
		{
			low[p] = min(low[p], dfn[i]);
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
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	if(sc == 1)
	{
		printf("%d\n", sz[sc]);
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(!g[i][j])continue;
			G[scc[i]][scc[j]] = 1;
		}
	}
	for(int i = 1; i <= sc; i++)
	{
		for(int j = 1; j <= sc; j++)
		{
			if(!G[i][j] || i == j)continue;
			for(int k = 1; k <= sc; k++)
			{
				if(!G[j][k] || i == k || j == k)continue;
				G[i][k] = 0;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= sc; i++)
		for(int j = 1; j <= sc; j++)
			if(i != j && G[i][j])ans++;
	for(int i = 1; i <= sc; i++)
		if(sz[i] != 1)ans += sz[i];
	printf("%d\n", ans);
	return 0;
}