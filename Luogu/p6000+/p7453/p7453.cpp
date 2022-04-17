#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 250010;
const ll p = 998244353;
struct Matrix
{
	int n, m;
	ll a[5][5];
	Matrix() {}
	Matrix(int _n, int _m) :n(_n), m(_m)
	{
		memset(a, 0, sizeof(a));
	}
	Matrix operator + (const Matrix &rhs)
	{
		Matrix res(n, m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				res.a[i][j] = (a[i][j] + rhs.a[i][j]) % p;
		return res;
	}
	Matrix operator * (const Matrix &rhs)
	{
		Matrix res(n, rhs.m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= rhs.m; j++)
				for(int k = 1; k <= m; k++)
					res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % p;
		return res;
	}
};
Matrix num[N];
struct SegTree
{
	int l, r;
	Matrix sum, tag;
}tr[N << 2];
Matrix base1, base2, base3, base4, base5, base6;
Matrix base;
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	left.sum = left.sum * root.tag;
	rght.sum = rght.sum * root.tag;
	left.tag = left.tag * root.tag;
	rght.tag = rght.tag * root.tag;
	root.tag = base;
	return;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = num[l];
		tr[p].tag = base;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].tag = base;
	return;
}

void segadd(int p, int l, int r, Matrix k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].tag = tr[p].tag * k;
		tr[p].sum = tr[p].sum * k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	return;
}

Matrix segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	Matrix res(4, 4);
	if(l <= mid)res = res + segsum(p << 1, l, r);
	if(r > mid)res = res + segsum(p << 1 | 1, l, r);
	return res;
}

void init()
{
	base = Matrix(4, 4);
	for(int i = 1; i <= 4; i++)
		base.a[i][i] = 1;
	/*
	base1:| base2:| base3:
	1 0 0 | 1 0 0 | 1 0 1
	1 1 0 | 0 1 0 | 0 1 0
	0 0 1 | 0 1 1 | 0 0 1
	*/
	base1 = base;
	base1.a[2][1] = 1;
	base2 = base;
	base2.a[3][2] = 1;
	base3 = base;
	base3.a[1][3] = 1;
	/*
	base4:  | base5:  | base6:
	1 0 0 0 | 1 0 0 0 | 1 0 0 0
	0 1 0 0 | 0 v 0 0 | 0 1 0 0
	0 0 1 0 | 0 0 1 0 | 0 0 0 0
	v 0 0 1 | 0 0 0 1 | 0 0 v 1
	*/
	base4 = base;
	base5 = base;
	base6 = base;
	base6.a[3][3] = 0;
}
int main()
{
	init();
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		num[i] = Matrix(1, 4);
		scanf("%lld%lld%lld", &num[i].a[1][1], &num[i].a[1][2], &num[i].a[1][3]);
		num[i].a[1][4] = 1;
	}
	build(1, 1, n);
	int m;
	scanf("%d", &m);
	while(m--)
	{
		int op, l, r, v;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			segadd(1, l, r, base1);
		}
		else if(op == 2)
		{
			segadd(1, l, r, base2);
		}
		else if(op == 3)
		{
			segadd(1, l, r, base3);
		}
		else if(op == 4)
		{
			scanf("%d", &v);
			base4.a[4][1] = v;
			segadd(1, l, r, base4);
		}
		else if(op == 5)
		{
			scanf("%d", &v);
			base5.a[2][2] = v;
			segadd(1, l, r, base5);
		}
		else if(op == 6)
		{
			scanf("%d", &v);
			base6.a[4][3] = v;
			segadd(1, l, r, base6);
		}
		else if(op == 7)
		{
			Matrix res = segsum(1, l, r);
			printf("%lld %lld %lld\n", res.a[1][1], res.a[1][2], res.a[1][3]);
		}
	}
	return 0;
}
