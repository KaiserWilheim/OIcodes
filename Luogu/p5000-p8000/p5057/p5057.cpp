#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 200010;
int a[N];
struct segtree
{
	int l, r, t;
	long long v;
}node[N << 2];
void build(int p, int l, int r)
{
	node[p].l = l;
	node[p].r = r;
	if(l == r)
	{
		node[p].v = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	node[p].v = node[p << 1].v + node[p << 1 | 1].v;
	return;
}
void tag(int p)
{
	auto &root = node[p], &left = node[p << 1], &rght = node[p << 1 | 1];
	if(node[p].t != 0)
	{
		left.t ^= root.t;
		rght.t ^= root.t;
		left.v = (left.r - left.l + 1) - left.v;
		rght.v = (rght.r - rght.l + 1) - rght.v;
		root.t = 0;
	}
	return;
}
void segpd(int p, int l, int r)
{
	if((node[p].r <= r) && (node[p].l >= l))
	{
		node[p].t ^= 1;
		node[p].v = (node[p].r - node[p].l + 1) - node[p].v;
		return;
	}
	if((node[p].r < l) || (node[p].l > r))return;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	if(mid >= l)segpd(p << 1, l, r);
	if(mid < r)segpd(p << 1 | 1, l, r);
	node[p].v = node[p << 1].v + node[p << 1 | 1].v;
	return;
}
long long segsum(int p, int l, int r)
{
	if((node[p].r <= r) && (node[p].l >= l))return node[p].v;
	if((node[p].r < l) || (node[p].l > r))return 0;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	long long ans = 0;
	if(mid >= l)ans += segsum(p << 1, l, r);
	if(mid < r)ans += segsum(p << 1 | 1, l, r);
	return ans;
}
int main()
{
	int m;
	scanf("%d%d", &n, &m);
	memset(a, 0, N);
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		scanf("%d%d", &op, &x);
		if(op == 1)
		{
			scanf("%d", &y);
			segpd(1, x, y);
		}
		else if(op == 2)
		{
			printf("%lld\n", segsum(1, x, x));
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
