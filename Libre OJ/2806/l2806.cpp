#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
ll w[M], c[N];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll sz[N], flen[N], slen[N], son[N];
ll f[N], g[N];
void dfs1(int p, int fa)
{
	sz[p] = c[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		int v = e[i];
		dfs1(v, p);
		sz[p] += sz[v];
		if(sz[v])
		{
			g[p] += g[v] + 2 * w[i];
			if(flen[v] + w[i] >= flen[p])
				slen[p] = flen[p], flen[p] = flen[v] + w[i], son[p] = v;
			else slen[p] = max(slen[p], flen[v] + w[i]);
		}
	}
}
void dfs2(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		int v = e[i];
		if(!sz[v])f[v] = f[p] + 2 * w[i], flen[v] = flen[p] + w[i];
		else if(m == sz[v])f[v] = g[v];
		else
		{
			f[v] = f[p];
			if(flen[v] < flen[p] + w[i] && son[p] != v)
				slen[v] = flen[v], flen[v] = flen[p] + w[i], son[v] = p;
			else if(flen[v] < slen[p] + w[i])
				slen[v] = flen[v], flen[v] = slen[p] + w[i], son[v] = 1;
			else if(slen[v] < flen[p] + w[i] && son[p] != v)
				slen[v] = flen[p] + w[i];
			else if(slen[v] < slen[p] + w[i])
				slen[v] = slen[p] + w[i];
		}
		dfs2(v, p);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		ll c;
		scanf("%d%d%lld", &a, &b, &c);
		add(a, b, c), add(b, a, c);
	}
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		c[x]++;
	}
	dfs1(1, 0);
	f[1] = g[1];
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
		printf("%lld\n", f[i] - flen[i]);
	return 0;
}