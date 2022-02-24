#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = N << 1;
int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct segtree
{
	int l, r;
	int add, max;
}tr[N << 3];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
	return;
}
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father) continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j]) son[p] = j;
	}
	return;
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = w[p], top[p] = t;
	if(!son[p]) return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
	return;
}
void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
	return;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.add)
	{
		left.add = left.add + root.add;
		left.max = left.max + root.add;
		rght.add = rght.add + root.add;
		rght.max = rght.max + root.add;
		root.add = 0;
	}
	return;
}
void build(int p, int l, int r)
{
	tr[p] = { l, r, 0, 0 };
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}
void segadd(int p, int l, int r, int k)
{
	if((l <= tr[p].l) && (r >= tr[p].r))
	{
		tr[p].add = (tr[p].add + k);
		tr[p].max = (tr[p].max + k);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid) segadd(p << 1, l, r, k);
	if(r > mid) segadd(p << 1 | 1, l, r, k);
	pushup(p);
	return;
}
int segmax(int p, int l, int r)
{
	if((l <= tr[p].l) && (r >= tr[p].r)) return tr[p].max;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid) res = max(res, segmax(p << 1, l, r));
	if(r > mid) res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
void addpath(int p, int q, int k)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]]) swap(p, q);
		segadd(1, id[top[p]], id[p], k);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q]) swap(p, q);
	segadd(1, id[q], id[p], k);
	return;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof h);
	for(int i = 0; i < n - 1; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	while(m--)
	{
		int s, t;
		scanf("%d%d", &s, &t);
		addpath(s, t, 1);
	}
	cout << segmax(1, 1, n) << endl;
	return 0;
}
