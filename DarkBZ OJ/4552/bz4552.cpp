#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
int q;
int a[N];
struct SegTree
{
	int l, r;
	int sum, tag;
}tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.tag != -1)
	{
		left.sum = (left.r - left.l + 1) * root.tag;
		rght.sum = (rght.r - rght.l + 1) * root.tag;
		left.tag = root.tag;
		rght.tag = root.tag;
		root.tag = -1;
	}
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
}
void init(int p, int k)
{
	tr[p].tag = -1;
	if(tr[p].l == tr[p].r)
	{
		tr[p].sum = (a[tr[p].l] >= k);
		tr[p].tag = -1;
		return;
	}
	init(p << 1, k);
	init(p << 1 | 1, k);
	pushup(p);
}
void segchg(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].sum = (tr[p].r - tr[p].l + 1) * k;
		tr[p].tag = k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segchg(p << 1, l, r, k);
	if(r > mid)segchg(p << 1 | 1, l, r, k);
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
int op[N], L[N], R[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &op[i], &L[i], &R[i]);
	scanf("%d", &q);
	build(1, 1, n);
	int ans = -1;
	int l = 1, r = n;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		init(1, mid);
		for(int i = 1; i <= m; i++)
		{
			int cnt = segsum(1, L[i], R[i]);
			if(op[i] == 0)
			{
				segchg(1, L[i], R[i] - cnt, 0);
				segchg(1, R[i] - cnt + 1, R[i], 1);
			}
			else if(op[i] == 1)
			{
				segchg(1, L[i], L[i] + cnt - 1, 1);
				segchg(1, L[i] + cnt, R[i], 0);
			}
		}
		int pos = segsum(1, q, q);
		if(pos == 1)
		{
			l = mid + 1;
			ans = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
