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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int x, y, a, b;
		scanf("%d%d%d%d", &x, &a, &y, &b);
		add(x + !a * n, y + b * n);
		add(y + !b * n, x + a * n);
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		if(scc[i] == scc[i + n])
		{
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts("POSSIBLE");
	for(int i = 1; i <= n; i++)
		if(scc[i] < scc[i + n])printf("0 ");
		else printf("1 ");
	return 0;
}
