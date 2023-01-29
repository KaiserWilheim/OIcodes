#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2000010, M = N << 1;
ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}
int n, k;
int a[N];
int c[N];
int dfn[N], sz[N], id[N], cnt;
int st[N], ed[N];
ll d[N], s[N], g[N];
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
void dfs1(int p, int fa)
{
	st[p] = cnt + 1;
	if(c[p])dfn[p] = ++cnt, id[cnt] = p;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		d[e[i]] = d[p] + w[i];
		dfs1(e[i], p);
		s[p] += s[e[i]] + c[e[i]] * w[i];
		c[p] += c[e[i]];
	}
	ed[p] = cnt;
}
void pushup(int p)
{
	g[p] = gcd(g[p << 1], g[p << 1 | 1]);
}
void build(int p, int l, int r)
{
	if(l == r)
	{
		g[p] = d[id[l]] - d[id[l - 1]];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, int x, ll w)
{
	if(x > k)return;
	if(l == r)
	{
		g[p] += w;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)segadd(p << 1, l, mid, x, w);
	else segadd(p << 1 | 1, mid + 1, r, x, w);
	pushup(p);
}
ll ans = 1e16;
void dfs2(int p, int fa)
{
	if(!g[1])ans = 0;
	else ans = min(ans, s[p] / abs(g[1]) * 2);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		ll tmps = s[e[i]], tmpc = c[e[i]];
		s[e[i]] = s[p] - c[e[i]] * w[i] + (c[p] - c[e[i]]) * w[i];
		c[e[i]] = c[p];
		segadd(1, 1, k, 1, w[i]);
		segadd(1, 1, k, st[e[i]], -2 * w[i]);
		segadd(1, 1, k, ed[e[i]] + 1, 2 * w[i]);
		dfs2(e[i], p);
		s[e[i]] = tmps, c[e[i]] = tmpc;
		segadd(1, 1, k, 1, -w[i]);
		segadd(1, 1, k, st[e[i]], 2 * w[i]);
		segadd(1, 1, k, ed[e[i]] + 1, -2 * w[i]);
	}
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++)
	{
		scanf("%d", &a[i]);
		c[a[i]] = 1;
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dfs1(1, 0);
	build(1, 1, k);
	dfs2(1, 0);
	printf("%lld\n", ans);
	return 0;
}
