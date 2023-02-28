#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
ll a[N], w[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], dep[N], son[N], sz[N], top[N];
int dfn[N], cnt;
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	top[p] = t, dfn[p] = ++cnt;
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
	ll tag;
	ll sum;
	void pushtag(ll v)
	{
		sum += v * (r - l + 1);
		tag += v;
	}
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void pushdown(int p)
{
	if(!tr[p].tag)return;
	tr[p << 1].pushtag(tr[p].tag);
	tr[p << 1 | 1].pushtag(tr[p].tag);
	tr[p].tag = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, ll k)
{
	if(l <= tr[p].l && tr[p].r <= r)
	{
		tr[p].pushtag(k);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
ll segsum(int p, int l, int r)
{
	if(l <= tr[p].l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
int lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
int sta[N], tt;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &w[i]);
	for(int i = 1; i <= n; i++)
	{
		while(tt && a[sta[tt]] < a[i])fa[sta[tt]] = i, tt--;
		sta[++tt] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		if(!fa[i])fa[i] = n + 1;
		add(fa[i], i), add(i, fa[i]);
	}
	dfs1(n + 1, 0);
	dfs2(n + 1, n + 1);
	build(1, 1, n + 1);
	for(int i = 1; i <= n; i++)
		segadd(1, dfn[i], dfn[i] + sz[i] - 1, w[i]);
	while(m--)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1)
		{
			segadd(1, dfn[x], dfn[x] + sz[x] - 1, y * 2);
			segadd(1, dfn[x], dfn[x], -y);
		}
		else
		{
			int g = lca(x, y), z = g;
			if(g == x || g == y)z = fa[z];
			if(!z || z == n + 1)
			{
				puts("?");
				continue;
			}
			ll ans = 0,
				num1 = segsum(1, dfn[fa[z]], dfn[fa[z]]),
				num2 = segsum(1, dfn[x], dfn[x]),
				num3 = segsum(1, dfn[y], dfn[y]),
				num4 = segsum(1, dfn[g], dfn[g]);
			ans += num2 - num1;
			ans += num3 - num1;
			ans -= num4 - num1;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
