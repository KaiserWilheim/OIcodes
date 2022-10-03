#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll sum[N][2], sz[N];
void dfs1(int p, int fa)
{
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
	}
}
void dfs2(int p, int fa, int k)
{
	sum[p][0] = 0, sum[p][1] = 1e18;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs2(e[i], p, k);
		sum[p][0] += sum[e[i]][0] + sz[e[i]] * (n - sz[e[i]]) * w[i];
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		sum[p][1] = min(sum[p][1], sum[p][0] - sum[e[i]][0] - sz[e[i]] * (n - sz[e[i]]) * w[i] + min(sum[e[i]][0], sum[e[i]][1]) + (sz[k] - sz[e[i]]) * (n - sz[k] + sz[e[i]]) * w[i]);
	}
}
struct Edge
{
	int u, v;
	ll w;
};
Edge ed[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
		ed[i] = { u,v,w };
	}
	ll ans = 1e18;
	for(int i = 1; i < n; i++)
	{
		int v = ed[i].v, u = ed[i].u;
		dfs1(u, v), dfs1(v, u);
		dfs2(u, v, u), dfs2(v, u, v);
		ans = min(ans, min(sum[u][0], sum[u][1]) + min(sum[v][0], sum[v][1]) + sz[u] * sz[v] * ed[i].w);
	}
	printf("%lld\n", ans);
	return 0;
}