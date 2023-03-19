#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 600010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], tot;
int sta[N], tt;
vector<int>scc[N];
int sc, sz[N];
void tarjan(int p, int fa)
{
	dfn[p] = low[p] = ++tot;
	sta[++tt] = p;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j, p);
			low[p] = min(low[p], low[j]);
		}
		else if(j != fa)
			low[p] = min(low[p], dfn[j]);
	}
	if(dfn[p] == low[p])
	{
		sc++;
		while(sta[tt] != p)
		{
			scc[sc].push_back(sta[tt]);
			sz[sc]++;
			tt--;
		}
		scc[sc].push_back(sta[tt]);
		sz[sc]++;
		tt--;
	}
}
int deg[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
		deg[u]++, deg[v]++;
	}
	if(m == 0)
	{
		puts("0 0");
		return 0;
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i, 0);
	if(sc == 1)
	{
		printf("1 %d\n", m);
		return 0;
	}
	int res = 0;
	for(int i = 1; i <= n; i++)res += deg[i] & 1;
	res >>= 1;
	for(int i = 1; i <= sc; i++)
	{
		int tmp = 0;
		for(auto v : scc[i])
			tmp += deg[v] >= 3;
		if(sz[i] != 1 && tmp <= 1)res++;
	}
	printf("%d %d\n", res, m);
	return 0;
}
