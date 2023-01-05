#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll INF = 1e16;
int n;
int h[N], e[M], ne[M], idx;
ll w[N], nw[N];
int deg[N];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc;
void tarjan(int p)
{
	dfn[p] = low[p] = ++cnt;
	sta[++tt] = p;
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[p] = min(low[p], low[v]);
		}
		else if(vis[v])
		{
			low[p] = min(low[p], dfn[v]);
		}
	}
	if(dfn[p] == low[p])
	{
		sc++;
		int sz = 0;
		do
		{
			vis[sta[tt]] = false;
			scc[sta[tt]] = sc;
			sz++;
		} while(sta[tt--] != p);
		if(sz == 1)scc[p] = 0, sc--;
	}
}
ll f[N][2], g[N][3];
ll ans;
int tmp[N], tot;
void dfs(int p)
{
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(scc[v])continue;
		dfs(v);
		ll tmp0 = f[p][0] + f[v][1] + w[i];
		ll tmp1 = min(f[p][0] + f[v][1], f[p][1] + f[v][1] + w[i]);
		f[p][0] = tmp0, f[p][1] = tmp1;
	}
}
void init(int p, int t)
{
	dfs(p);
	tmp[++tot] = p;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(scc[v])
		{
			nw[tot] = w[i];
			if(v != t)init(v, t);
		}
	}
}
void solve(int p)
{
	tot = 0;
	init(p, p);
	g[1][0] = nw[tot] + f[tmp[1]][0];
	g[1][1] = nw[tot] + f[tmp[1]][1];
	for(int i = 2; i <= tot; i++)
	{
		int u = tmp[i];
		g[i][0] = min(g[i - 1][0], g[i - 1][1] + nw[i - 1]) + f[u][0];
		g[i][1] = min(g[i - 1][0], g[i - 1][1] + nw[i - 1]) + f[u][1];
	}
	ll res = g[tot][1];
	g[1][0] = f[tmp[1]][0], g[1][1] = f[tmp[1]][1], g[1][2] = INF;
	for(int i = 2; i <= tot; i++)
	{
		int u = tmp[i];
		g[i][0] = min(g[i - 1][0], g[i - 1][1] + nw[i - 1]) + f[u][0];
		g[i][1] = min(g[i - 1][0], g[i - 1][1] + nw[i - 1]) + f[u][1];
		g[i][2] = min(g[i - 1][2], g[i - 1][1] + nw[i - 1]) + f[u][0];
	}
	ans += min(res, g[tot][2]);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int u, w;
		scanf("%d%d", &u, &w);
		add(u, i, w);
		deg[u]++;
	}
	bool flag = false;
	for(int i = 1; i <= n; i++)
		if(deg[i] != 1) { flag = true; break; }
	if(!flag)
	{
		int u = 1;
		while(!vis[u])vis[u] = 1, u = e[h[u]];
		for(int i = 1; i <= n; i++)
			if(!vis[i]) { flag = true; break; }
		if(!flag)
		{
			puts("0");
			return 0;
		}
	}
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
		if(!vis[i] && scc[i])solve(i);
	printf("%lld\n", ans);
	return 0;
}
