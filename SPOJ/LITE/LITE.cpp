#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
struct SegTree
{
	int l, r;
	int sum, tag;
}tr[N << 3];
int a[N];

void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.tag)
	{
		left.tag ^= 1;
		rght.tag ^= 1;
		left.sum = (left.r - left.l + 1) - left.sum;
		rght.sum = (rght.r - rght.l + 1) - rght.sum;
		root.tag ^= 1;
	}
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
void segadd(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].sum = (tr[p].r - tr[p].l + 1) - tr[p].sum;
		tr[p].tag ^= 1;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r);
	if(r > mid)segadd(p << 1 | 1, l, r);
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

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	while(m--)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 0)
		{
			segadd(1, x, y);
		}
		else if(op == 1)
		{
			printf("%d\n", segsum(1, x, y));
		}
	}
	return 0;
}
