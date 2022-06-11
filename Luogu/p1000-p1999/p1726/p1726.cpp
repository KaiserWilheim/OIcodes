#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int op, u, v;
		scanf("%d%d%d", &u, &v, &op);
		add(u, v);
		if(op == 2)add(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	int maxn = 0, maxp = 0;
	for(int i = 1; i <= sc; i++)
	{
		if(sz[i] > maxn)
		{
			maxn = sz[i];
			maxp = i;
		}
	}
	printf("%d\n", maxn);
	for(int i = 1; i <= n; i++)
		if(scc[i] == maxp)printf("%d ", i);
	putchar('\n');
	return 0;
}
