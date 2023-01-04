#include<bits/stdc++.h>
#define int long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
int dep[N], sz[N], fa[N], son[N], top[N];
int id[N], w[N], nw[N], cnt;

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int p, int father, int depth)
{
	fa[p] = father, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[j] > sz[son[p]])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = w[p], top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p])continue;
		dfs2(j, j);
	}
}

namespace pos
{
	struct segtree
	{
		int l, r;
		int sum, cnt, tag;
	}tr[N << 3];
	void pushup(int p)
	{
		tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
		tr[p].cnt = tr[p << 1].cnt + tr[p << 1 | 1].cnt;
	}
	void pushdown(int p)
	{
		segtree &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
		left.sum += root.tag * left.cnt;
		rght.sum += root.tag * rght.cnt;
		left.tag += root.tag;
		rght.tag += root.tag;
		root.tag = 0;
	}
	void build(int p, int l, int r)
	{
		tr[p].l = l, tr[p].r = r;
		tr[p].sum = tr[p].cnt = tr[p].tag = 0;
		if(l == r)return;
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
	}
	void segchg(int p, int pos, int k)
	{
		if(tr[p].l == tr[p].r)
		{
			tr[p].sum = k;
			tr[p].cnt = 1;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(pos <= mid)segchg(p << 1, pos, k);
		else segchg(p << 1 | 1, pos, k);
		pushup(p);
	}
	void segadd(int p, int l, int r, int k)
	{
		if(tr[p].l >= l && tr[p].r <= r)
		{
			tr[p].sum += tr[p].cnt * k;
			tr[p].tag += k;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)segadd(p << 1, l, r, k);
		if(r > mid)segadd(p << 1 | 1, l, r, k);
		pushup(p);
	}
	int segsum(int p, int l, int r)
	{
		if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
		if(tr[p].tag)pushdown(p);
		int res = 0;
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)res += segsum(p << 1, l, r);
		if(r > mid)res += segsum(p << 1 | 1, l, r);
		return res;
	}
}
namespace neg
{
	struct segtree
	{
		int l, r;
		int sum, cnt, max, tag;
	}tr[N << 3];
	void pushup(int p)
	{
		tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
		tr[p].cnt = tr[p << 1].cnt + tr[p << 1 | 1].cnt;
		tr[p].max = std::max(tr[p << 1].max, tr[p << 1 | 1].max);
	}
	void pushdown(int p)
	{
		segtree &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
		left.sum += root.tag * left.cnt;
		rght.sum += root.tag * rght.cnt;
		left.max += root.tag;
		rght.max += root.tag;
		left.tag += root.tag;
		rght.tag += root.tag;
		root.tag = 0;
	}
	void build(int p, int l, int r)
	{
		tr[p].l = l, tr[p].r = r;
		tr[p].sum = tr[p].cnt = tr[p].tag = 0;
		tr[p].max = -1e18;
		if(l == r)return;
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
	}
	void segchg(int p, int pos, int k)
	{
		if(tr[p].l == tr[p].r)
		{
			tr[p].sum = k;
			tr[p].max = k;
			tr[p].cnt = 1;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(pos <= mid)segchg(p << 1, pos, k);
		else segchg(p << 1 | 1, pos, k);
		pushup(p);
	}
	void chq(int p)
	{
		if(tr[p].max < 0)return;
		if(tr[p].l == tr[p].r)
		{
			pos::segchg(1, tr[p].l, tr[p].max);
			tr[p].sum = tr[p].cnt = 0;
			tr[p].max = -1e18;
			return;
		}
		if(tr[p].tag)pushdown(p);
		chq(p << 1);
		chq(p << 1 | 1);
		pushup(p);
	}
	void segadd(int p, int l, int r, int k)
	{
		if(tr[p].l >= l && tr[p].r <= r)
		{
			tr[p].sum += tr[p].cnt * k;
			tr[p].max += k;
			tr[p].tag += k;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)segadd(p << 1, l, r, k);
		if(r > mid)segadd(p << 1 | 1, l, r, k);
		pushup(p);
	}
	int segsum(int p, int l, int r)
	{
		if(!tr[p].cnt)return 0;
		if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
		if(tr[p].tag)pushdown(p);
		int res = 0;
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)res += segsum(p << 1, l, r);
		if(r > mid)res += segsum(p << 1 | 1, l, r);
		return res;
	}
}

void segadd(int l, int r, int k)
{
	pos::segadd(1, l, r, k);
	neg::segadd(1, l, r, k);
	neg::chq(1);
}
int segsum(int l, int r)
{
	return pos::segsum(1, l, r) - neg::segsum(1, l, r);
}

void addpath(int p, int q, int k)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])std::swap(p, q);
		segadd(id[top[p]], id[p], k);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])std::swap(p, q);
	segadd(id[q], id[p], k);
}
int sumpath(int p, int q)
{
	int res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])std::swap(p, q);
		res += segsum(id[top[p]], id[p]);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])std::swap(p, q);
	res += segsum(id[q], id[p]);
	return res;
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &w[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%lld%lld", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	pos::build(1, 1, n);
	neg::build(1, 1, n);
	for(int i = 1; i <= n; i++)
	{
		if(w[i] >= 0)pos::segchg(1, id[i], w[i]);
		else neg::segchg(1, id[i], w[i]);
	}
	while(m--)
	{
		int op, u, v;
		scanf("%lld%lld%lld", &op, &u, &v);
		if(op == 1)
		{
			int k;
			scanf("%lld", &k);
			addpath(u, v, k);
		}
		else
		{
			printf("%lld\n", sumpath(u, v));
		}
	}
	return 0;
}
