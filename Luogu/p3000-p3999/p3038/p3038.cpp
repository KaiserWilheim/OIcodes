#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct segtree
{
	int l, r;
	ll add, sum;
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
	tr[p].sum = (tr[p << 1].sum + tr[p << 1 | 1].sum);
	return;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.add)
	{
		left.add = (left.add + root.add);
		left.sum = (left.sum + root.add * (left.r - left.l + 1));
		rght.add = (rght.add + root.add);
		rght.sum = (rght.sum + root.add * (rght.r - rght.l + 1));
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
		tr[p].sum = (tr[p].sum + k * (tr[p].r - tr[p].l + 1));
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid) segadd(p << 1, l, r, k);
	if(r > mid) segadd(p << 1 | 1, l, r, k);
	pushup(p);
	return;
}
ll segsum(int p, int l, int r)
{
	if((l <= tr[p].l) && (r >= tr[p].r)) return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid) res += segsum(p << 1, l, r);
	if(r > mid) res += segsum(p << 1 | 1, l, r);
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
	segadd(1, id[q] + 1, id[p], k);
	return;
}
ll sumpath(int p, int q)
{
	ll res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]]) swap(p, q);
		res += segsum(1, id[top[p]], id[p]);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q]) swap(p, q);
	res += segsum(1, id[q] + 1, id[p]);
	return res;
}
void addtree(int p, int k)
{
	segadd(1, id[p], id[p] + sz[p] - 1, k);
	return;
}
ll sumtree(int p)
{
	return segsum(1, id[p], id[p] + sz[p] - 1);
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
		char op[10];
		int a, b;
		scanf("%s%d%d", op, &a, &b);
		if(op[0] == 'P')
		{
			addpath(a, b, 1);
		}
		else if(op[0] == 'Q')
		{
			printf("%lld\n", sumpath(a, b));
		}
	}
	return 0;
}
