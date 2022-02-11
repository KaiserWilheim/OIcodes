#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int N = 100010;
int n, m;
int cnt, h[N], e[N << 1], ne[N << 1], val[N << 1];
int idx, fa[N], son[N], top[N], dep[N], dfn[N], sz[N], tmp[N], w[N];
struct SegTree
{
	int l, r;
	int max;
}tr[N << 3];
struct node
{
	int x, y;
}id[N];
inline void add(int x, int y, int w)
{
	ne[++cnt] = h[x]; e[cnt] = y; val[cnt] = w; h[x] = cnt;
}
inline void dfs1(int x, int f)
{
	dep[x] = dep[f] + 1; fa[x] = f; sz[x] = 1;
	for(int i = h[x]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == f) continue;
		dfs1(v, x);
		tmp[v] = val[i];
		sz[x] += sz[v];
		if(sz[son[x]] < sz[v]) son[x] = v;
	}
}
inline void dfs2(int x, int topf)
{
	dfn[x] = ++idx; w[idx] = tmp[x]; top[x] = topf;
	if(son[x]) dfs2(son[x], topf);
	for(int i = h[x]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa[x] || v == son[x]) continue;
		dfs2(v, v);
	}
}
inline void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
}
inline void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].max = w[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
inline void change(int p, int q, int k)
{
	if((tr[p].l == q) && (tr[p].r == q))
	{
		tr[p].max = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(q <= mid) change(p << 1, q, k);
	if(q > mid)  change(p << 1 | 1, q, k);
	pushup(p);
}
inline int segmax(int p, int l, int r)
{
	if((l <= tr[p].l) && (r >= tr[p].r))return tr[p].max;
	int res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
inline int maxpath(int x, int y)
{
	int res = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res = max(res, segmax(1, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) res = max(res, segmax(1, dfn[x] + 1, dfn[y]));
	return res;
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
		id[i].x = a;
		id[i].y = b;
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	char s[10];
	scanf("%s", s);
	while(s[0] != 'D')
	{
		int a, b;
		scanf("%lld%lld", &a, &b);
		if(s[0] == 'C')
		{
			int tmpp;
			if(dep[id[a].x] > dep[id[a].y]) tmpp = id[a].x;
			else tmpp = id[a].y;
			change(1, dfn[tmpp], b);
		}
		else if(s[0] == 'Q')
		{
			if(a == b)puts("0");
			else printf("%lld\n", maxpath(a, b));
		}
		scanf("%s", s);
	}
	return 0;
}
