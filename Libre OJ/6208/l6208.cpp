#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct Matrix
{
	int a[4][4];
	int m, n;
	Matrix(int _m, int _n)
	{
		m = _m, n = _n;
		memset(a, 0, sizeof(a));
	}
	friend Matrix operator + (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix ans(lhs.m, lhs.n);
		for(int i = 1; i <= lhs.m; i++)
			for(int j = 1; j <= lhs.n; j++)
				ans.a[i][j] = lhs.a[i][j] + rhs.a[i][j];
		return ans;
	}
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix ans(lhs.m, rhs.n);
		for(int i = 1; i <= lhs.m; i++)
			for(int j = 1; j <= rhs.n; j++)
				for(int k = 1; k <= lhs.n; k++)
					ans.a[i][j] += lhs.a[i][k] * rhs.a[k][j];
		return ans;
	}
	friend bool operator != (const Matrix &lhs, const Matrix &rhs)
	{
		for(int i = 1; i <= lhs.m; i++)
			for(int j = 1; j <= lhs.n; j++)
				if(lhs.a[i][j] != rhs.a[i][j])
					return true;
		return false;
	}
};

const int N = 100010, M = N << 1;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N], fa[N], son[N], sz[N];
int top[N], id[N], cnt;
void dfs1(int p, int father, int depth)
{
	fa[p] = father, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	top[p] = t, id[p] = ++cnt;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == son[p] || j == fa[p])continue;
		dfs2(j, j);
	}
}

struct SegTree
{
	int l, r;
	Matrix sum = Matrix(1, 3), tag = Matrix(3, 3);
}tr[N << 3];
Matrix base(3, 3);
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].sum.a[1][3] = 1;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.tag != base)
	{
		left.sum = left.sum * root.tag;
		left.tag = left.tag * root.tag;
		rght.sum = rght.sum * root.tag;
		rght.tag = rght.tag * root.tag;
		root.tag = base;
	}
}

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r, tr[p].tag = base;
	if(l == r)
	{
		tr[p].sum.a[1][3] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}
void segadd(int p, int l, int r, Matrix k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].sum = tr[p].sum * k;
		tr[p].tag = tr[p].tag * k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum.a[1][2];
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}

void addpath(int p, int q, Matrix k)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		segadd(1, id[top[p]], id[p], k);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	segadd(1, id[q], id[p], k);
	return;
}
int main()
{
	memset(h, -1, sizeof(h));
	int n;
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	base.a[1][1] = 1;
	base.a[2][2] = 1;
	base.a[3][3] = 1;
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	int m;
	scanf("%d", &m);
	while(m--)
	{
		int op, x, d;
		scanf("%d%d", &op, &x);
		if(op == 1)
		{
			scanf("%d", &d);
			Matrix k = base;
			k.a[3][1] = d;
			addpath(1, x, k);
		}
		else if(op == 2)
		{
			scanf("%d", &d);
			Matrix k = base;
			k.a[1][2] = d;
			addpath(1, x, k);
		}
		else if(op == 3)
		{
			printf("%d\n", segsum(1, id[x], id[x]));
		}
	}
	return 0;
}
