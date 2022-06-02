#include<iostream>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m, p;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
int ind[N], out[N];
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
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		while(x)
		{
			add(i, x);
			scanf("%d", &x);
		}
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	if(sc == 1)
	{
		puts("1\n0");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = h[i]; ~j; j = ne[j])
		{
			int v = e[j];
			if(scc[i] != scc[v])
			{
				ind[scc[v]]++;
				out[scc[i]]++;
			}
		}
	}
	int cnti = 0, cnto = 0;
	for(int i = 1; i <= sc; i++)
	{
		if(!ind[i])cnti++;
		if(!out[i])cnto++;
	}
	printf("%d\n%d\n", cnti, max(cnti, cnto));
	return 0;
}
