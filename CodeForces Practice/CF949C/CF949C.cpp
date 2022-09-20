#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 400010;
int n, m, k;
int h[N], e[M], ne[M], idx;
int mnt[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int low[N], dfn[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sz[N], sc;
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
int oud[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &mnt[i]);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if((mnt[u] + 1) % k == mnt[v] % k)add(u, v);
		if((mnt[v] + 1) % k == mnt[u] % k)add(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		int u = scc[i];
		for(int j = h[i]; ~j; j = ne[j])
		{
			int v = scc[e[j]];
			if(u != v)oud[u]++;
		}
	}
	int ans = 0;
	sz[0] = 998244353;
	for(int i = 1; i <= sc; i++)
	{
		if(oud[i] == 0)
		{
			ans = (sz[ans] > sz[i]) ? i : ans;
		}
	}
	printf("%d\n", sz[ans]);
	for(int i = 1; i <= n; i++)
		if(scc[i] == ans)printf("%d ", i);
	putchar('\n');
	return 0;
}