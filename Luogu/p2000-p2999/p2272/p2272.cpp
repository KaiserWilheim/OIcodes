#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 2000010;
int n, m;
int mod;
int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
int ind[N], out[N];
int f[N], g[N];
void add(int h[], int a, int b)
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
	memset(hs, -1, sizeof(hs));
	scanf("%d%d%d", &n, &m, &mod);
	while(m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(h, a, b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	unordered_set<ll>S;
	for(int i = 1; i <= n; i++)
	{
		for(int j = h[i]; ~j; j = ne[j])
		{
			int k = e[j];
			int a = scc[i], b = scc[k];
			ll hash = a * 1000000ll + b;
			if(a != b && !S.count(hash))
			{
				add(hs, a, b);
				S.insert(hash);
			}
		}
	}
	for(int i = sc; i; i--)
	{
		if(!f[i])
		{
			f[i] = sz[i];
			g[i] = 1;
		}
		for(int j = hs[i]; ~j; j = ne[j])
		{
			int k = e[j];
			if(f[k] < f[i] + sz[k])
			{
				f[k] = f[i] + sz[k];
				g[k] = g[i];
			}
			else if(f[k] == f[i] + sz[k])
				g[k] = (g[k] + g[i]) % mod;
		}
	}
	int maxf = 0, sum = 0;
	for(int i = 1; i <= sc; i++)
	{
		if(f[i] > maxf)
		{
			maxf = f[i];
			sum = g[i];
		}
		else if(f[i] == maxf) sum = (sum + g[i]) % mod;
	}
	printf("%d\n", maxf);
	printf("%d\n", sum);
	return 0;
}
