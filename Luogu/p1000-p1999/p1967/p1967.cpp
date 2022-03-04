#include<bits/stdc++.h>
#define N 500020
#define inf 0x7f7f7f7f
#define ll long long
using namespace std;
struct Edge
{
	int u, v, w, next;
}G[N];
int tot = 0, head[4 * N];
int sz[N], wson[N], fa[N], d[N], top[N];
int tpos[N], pre[N], cnt = 0;
bool vis[500005];
int a[N * 4], maxv[N * 4], minv[N * 4];
inline void addedge(int u, int v, int w)
{
	G[++tot].v = v; G[tot].u = u; G[tot].next = head[u]; head[u] = tot; G[tot].w = w;
	G[++tot].v = u; G[tot].u = v; G[tot].next = head[v]; head[v] = tot; G[tot].w = w;
}
struct Tree
{
	int u, v, w;
	bool operator < (const Tree &x)const
	{
		return w > x.w;
	}
}T[N];
int ff[N], n, m;
inline void read(int &x)
{
	x = 0; int f = 1; char ch;
	do { ch = getchar(); if(ch == '-')f = -1; } while(ch < '0' || ch>'9');
	do { x = x * 10 + ch - '0'; ch = getchar(); } while(ch >= '0' && ch <= '9');
	x *= f;
}
inline void readl(long long &x)
{
	x = 0; int f = 1; char ch;
	do { ch = getchar(); if(ch == '-')f = -1; } while(ch < '0' || ch>'9');
	do { x = x * 10 + ch - '0'; ch = getchar(); } while(ch >= '0' && ch <= '9');
	x *= f;
}
int find(int x)
{
	if(x == ff[x])return x;
	else return ff[x] = find(ff[x]);
}
void Kruskal()
{
	sort(T + 1, T + m + 1);
	for(int i = 1; i <= n; i++)ff[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int u = T[i].u, v = T[i].v, w = T[i].w;
		int x = find(u), y = find(v);
		if(x != y)addedge(u, v, w), ff[ff[u]] = ff[v];
	}
}
void dfs1(int u, int father)
{
	sz[u] = 1;
	for(int i = head[u]; i; i = G[i].next)
	{
		int v = G[i].v;
		if(v == father)continue;
		d[v] = d[u] + 1; fa[v] = u;
		a[v] = G[i].w; dfs1(v, u);
		sz[u] += sz[v];
		if(sz[v] > sz[wson[u]])wson[u] = v;
	}
}
void dfs2(int u, int TP)
{
	tpos[u] = ++cnt; pre[cnt] = u; top[u] = TP;
	if(wson[u])dfs2(wson[u], TP);
	for(int i = head[u]; i; i = G[i].next)
	{
		int v = G[i].v;
		if(v == fa[u] || v == wson[u])continue;
		dfs2(v, v);
	}
}
int LCA(int x, int y)
{
	while(top[x] != top[y])
	{
		if(d[top[x]] < d[top[y]])swap(x, y);
		x = fa[top[x]];
	}
	if(d[x] > d[y]) swap(x, y);
	return x;
}
inline void pushup(int o)
{
	maxv[o] = max(maxv[o * 2], maxv[o * 2 + 1]);
	minv[o] = min(minv[o * 2], minv[o * 2 + 1]);
}
void build(int o, int l, int r)
{
	int mid = (l + r) / 2;
	if(l == r) { maxv[o] = minv[o] = a[pre[l]]; return; }
	build(o * 2, l, mid); build(o * 2 + 1, mid + 1, r);
	pushup(o);
}
int querymax(int o, int l, int r, int ql, int qr)
{
	int mid = (l + r) / 2, ans = -inf;
	if(ql <= l && r <= qr)return maxv[o];
	if(ql <= mid)ans = max(ans, querymax(o * 2, l, mid, ql, qr));
	if(qr > mid)ans = max(ans, querymax(o * 2 + 1, mid + 1, r, ql, qr));
	pushup(o);
	return ans;
}
int querymin(int o, int l, int r, int ql, int qr)
{
	if(l > r) return 2147483647;
	int mid = (l + r) / 2, ans = inf;
	if(ql <= l && r <= qr)return minv[o];
	if(ql <= mid)ans = min(ans, querymin(o * 2, l, mid, ql, qr));
	if(qr > mid)ans = min(ans, querymin(o * 2 + 1, mid + 1, r, ql, qr));
	return ans;
}
int qmax(int u, int v)
{
	int ans = -inf;
	while(top[u] != top[v])
	{
		if(d[top[u]] < d[top[v]])swap(u, v);
		ans = max(ans, querymax(1, 1, n, tpos[top[u]], tpos[u]));
		u = fa[top[u]];
	}
	if(d[u] < d[v])swap(u, v);
	ans = max(ans, querymax(1, 1, n, tpos[v], tpos[u]));
	return ans;
}
int qmin(int u, int v)
{
	int ans = inf;
	while(top[u] != top[v])
	{
		if(d[top[u]] < d[top[v]])swap(u, v);
		ans = min(ans, querymin(1, 1, n, tpos[top[u]], tpos[u]));
		u = fa[top[u]];
	}
	if(d[u] < d[v])swap(u, v);
	ans = min(ans, querymin(1, 1, n, tpos[v] + 1, tpos[u]));
	return ans;
}
int main()
{
	memset(a, -1, sizeof(a));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		T[i].u = u; T[i].v = v; T[i].w = w;
	}
	Kruskal();
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		int xx = find(x), yy = find(y);
		if(xx != yy)printf("-1\n");
		else printf("%d\n", qmin(x, y));
	}
	return 0;
}
