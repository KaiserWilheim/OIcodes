#include <bits/stdc++.h>
using namespace std;
int n, m, d;
const int N = 100010;
int a[N];
struct segtree
{
	int l, r;
	long long v, ta, tm;
}node[N << 2];
void build(int p, int l, int r)
{
	node[p].l = l, node[p].r = r, node[p].ta = 0, node[p].tm = 1;
	if(l == r)
	{
		node[p].v = a[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	node[p].v = (node[p << 1].v + node[p << 1 | 1].v) % d;
	return;
}
void tag(int p)
{
	auto &root = node[p], &left = node[p << 1], &rght = node[p << 1 | 1];
	if((root.ta != 0) || (root.tm != 1))
	{
		left.tm = (left.tm * root.tm) % d, left.ta = (left.ta * root.tm + root.ta) % d;
		rght.tm = (rght.tm * root.tm) % d, rght.ta = (rght.ta * root.tm + root.ta) % d;
		left.v = (left.v * root.tm + root.ta * (left.r - left.l + 1)) % d;
		rght.v = (rght.v * root.tm + root.ta * (rght.r - rght.l + 1)) % d;
		root.ta = 0, root.tm = 1;
	}
	return;
}
void segadd(int p, int l, int r, int k)
{
	if((node[p].r <= r) && (node[p].l >= l))
	{
		node[p].ta = (node[p].ta + k) % d;
		node[p].v = (node[p].v + k * (node[p].r - node[p].l + 1)) % d;
		return;
	}
	if((node[p].r < l) || (node[p].l > r))return;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	if(mid >= l)segadd(p << 1, l, r, k);
	if(mid < r)segadd(p << 1 | 1, l, r, k);
	node[p].v = (node[p << 1].v + node[p << 1 | 1].v) % d;
	return;
}
void segmul(int p, int l, int r, int k)
{
	if((node[p].r <= r) && (node[p].l >= l))
	{
		node[p].tm = (node[p].tm * k) % d;
		node[p].ta = (node[p].ta * k) % d;
		node[p].v = (node[p].v * k) % d;
		return;
	}
	if((node[p].r < l) || (node[p].l > r))return;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	if(mid >= l)segmul(p << 1, l, r, k);
	if(mid < r)segmul(p << 1 | 1, l, r, k);
	node[p].v = (node[p << 1].v + node[p << 1 | 1].v) % d;
	return;
}
long long segsum(int p, int l, int r)
{
	if((node[p].r <= r) && (node[p].l >= l))return node[p].v;
	if((node[p].r < l) || (node[p].l > r))return 0;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	long long ans = 0;
	if(mid >= l)ans = ans + segsum(p << 1, l, r);
	if(mid < r)ans = ans + segsum(p << 1 | 1, l, r);
	return ans % d;
}
int main()
{
	scanf("%d%d", &n, &d);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int x, y, k;
			scanf("%d%d%d", &x, &y, &k);
			segmul(1, x, y, k);
		}
		else if(op == 2)
		{
			int x, y, k;
			scanf("%d%d%d", &x, &y, &k);
			segadd(1, x, y, k);
		}
		else if(op == 3)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%lld\n", segsum(1, x, y));
		}
	}
}
