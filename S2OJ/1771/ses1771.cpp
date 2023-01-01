#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int INF = 1e9;
int n, m;
struct SegTree
{
	int l, r;
	int tl, tr, td;
	friend SegTree operator + (const SegTree &lhs, const SegTree &rhs)
	{
		if(lhs.tr < rhs.tl - lhs.td)return { lhs.l,rhs.r,rhs.tl - lhs.td,rhs.tl - lhs.td,lhs.td + rhs.td };
		if(lhs.tl > rhs.tr - lhs.td)return { lhs.l,rhs.r,rhs.tr - lhs.td,rhs.tr - lhs.td,lhs.td + rhs.td };
		return { lhs.l,rhs.r,max(lhs.tl,rhs.tl - lhs.td),min(lhs.tr,rhs.tr - lhs.td),lhs.td + rhs.td };
	}
};
SegTree tr[N << 3];
int a[N], b[N];
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		if(a[l] == 1)tr[p].tl = -INF, tr[p].tr = INF, tr[p].td = b[l];
		if(a[l] == 2)tr[p].tl = -INF, tr[p].tr = b[l], tr[p].td = 0;
		if(a[l] == 3)tr[p].tl = b[l], tr[p].tr = INF, tr[p].td = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
void segchg(int p, int pos, int op, int val)
{
	if(tr[p].l == tr[p].r)
	{
		if(op == 1)tr[p].tl = -INF, tr[p].tr = INF, tr[p].td = val;
		if(op == 2)tr[p].tl = -INF, tr[p].tr = val, tr[p].td = 0;
		if(op == 3)tr[p].tl = val, tr[p].tr = INF, tr[p].td = 0;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos, op, val);
	else segchg(p << 1 | 1, pos, op, val);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
int calc(int x)
{
	if(x < tr[1].tl)return tr[1].tl + tr[1].td;
	if(x > tr[1].tr)return tr[1].tr + tr[1].td;
	return x + tr[1].td;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &b[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int op, x, v;
		scanf("%d%d", &op, &x);
		if(op <= 3)
		{
			scanf("%d", &v);
			segchg(1, x, op, v);
		}
		else
		{
			printf("%d\n", calc(x));
		}
	}
	return 0;
}