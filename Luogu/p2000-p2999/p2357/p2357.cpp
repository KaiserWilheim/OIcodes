#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
struct SegTree
{
	int l, r;
	ll sum, tag;
}tr[N << 3];
ll a[N];

void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.tag)
	{
		left.sum += root.tag * (left.r - left.l + 1);
		rght.sum += root.tag * (rght.r - rght.l + 1);
		left.tag += root.tag;
		rght.tag += root.tag;
		root.tag = 0;
	}
	return;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}

void segadd(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].tag += k;
		tr[p].sum += k * (tr[p].r - tr[p].l + 1);
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
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	ll res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	build(1, 1, n);
	while(m--)
	{
		int op, x, y, k;
		scanf("%d", &op);
		if(op == 5)
		{
			printf("%lld\n", segsum(1, 1, 1));
			continue;
		}
		scanf("%d", &x);
		if(op == 1)
		{
			scanf("%d%d", &y, &k);
			segadd(1, x, y, k);
		}
		else if(op == 2)
		{
			segadd(1, 1, 1, x);
		}
		else if(op == 3)
		{
			segadd(1, 1, 1, -x);
		}
		else if(op == 4)
		{
			scanf("%d", &y);
			printf("%lld\n", segsum(1, x, y));
		}
	}
	return 0;
}
