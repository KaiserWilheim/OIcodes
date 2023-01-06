#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 600010;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], son[N], dep[N], sz[N], top[N];
int dfn[N], id[N], nw[N], tot;
int tmpw[N];
void dfs1(int p, int fa, int depth)
{
	::fa[p] = fa, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p, depth + 1);
		tmpw[e[i]] = w[i];
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	dfn[p] = ++tot, id[tot] = p, nw[tot] = tmpw[p], top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
}
struct SegTree
{
	int l, r;
	int maxn, maxs;
};
SegTree tr[N << 3];
pair<int, int> merge(pair<int, int>lhs, pair<int, int>rhs)
{
	pair<int, int>res;
	if(lhs.first > rhs.first)
	{
		res.first = lhs.first;
		res.second = max(lhs.second, rhs.first);
	}
	else if(lhs.first < rhs.first)
	{
		res.first = rhs.first;
		res.second = max(rhs.second, lhs.first);
	}
	else
	{
		res.first = lhs.first;
		res.second = max(lhs.second, rhs.second);
	}
	return res;
}
void pushup(int p)
{
	pair<int, int>res = merge(make_pair(tr[p << 1].maxn, tr[p << 1].maxs),
		make_pair(tr[p << 1 | 1].maxn, tr[p << 1 | 1].maxs));
	tr[p].maxn = res.first;
	tr[p].maxs = res.second;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].maxn = nw[l];
		tr[p].maxs = -1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
pair<int, int> segmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return make_pair(tr[p].maxn, tr[p].maxs);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(r <= mid)return segmax(p << 1, l, r);
	else if(l > mid)return segmax(p << 1 | 1, l, r);
	else return merge(segmax(p << 1, l, r), segmax(p << 1 | 1, l, r));
}
pair<int, int> maxpath(int p, int q)
{
	pair<int, int>res = make_pair(-1, -1);
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		res = merge(res, segmax(1, dfn[top[p]], dfn[p]));
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	if(p != q)res = merge(res, segmax(1, dfn[q] + 1, dfn[p]));
	return res;
}
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &rhs)const
	{
		return w < rhs.w;
	}
};
Edge edge[M];
bool vis[M];
struct DSU
{
	int fa[N];
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
			fa[i] = i;
	}
	int find(int x)
	{
		if(fa[x] != x)fa[x] = find(fa[x]);
		return fa[x];
	}
	bool soyuz(int u, int v)
	{
		int fu = find(u), fv = find(v);
		if(fu != fv)
		{
			fa[fv] = fu;
			return true;
		}
		else return false;
	}
};
DSU dsu;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	dsu.init(n);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = { u,v,w };
	}
	sort(edge + 1, edge + 1 + m);
	int cnt = n;
	ll ans = 0;
	for(int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v;
		if(!dsu.soyuz(u, v))continue;
		int w = edge[i].w;
		ans += w;
		cnt--;
		add(u, v, w), add(v, u, w);
		vis[i] = true;
		if(cnt == 1)break;
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	int res = 1e9;
	for(int i = 1; i <= m; i++)
	{
		if(vis[i])continue;
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		if(u == v)continue;
		pair<int, int>k = maxpath(u, v);
		if(w != k.first)res = min(res, w - k.first);
		else if(k.second != -1)res = min(res, w - k.second);
	}
	printf("%lld\n", ans + res);
	return 0;
}
