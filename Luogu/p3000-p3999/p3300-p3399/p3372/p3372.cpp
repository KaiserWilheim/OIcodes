#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 100010;
int a[N];
struct segtree
{
	int l, r;
    long long v, t;
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
	if(node[p].t != 0)
	{
		node[p << 1].t += node[p].t;
		node[p << 1 | 1].t += node[p].t;
		node[p << 1].v += node[p].t * (node[p << 1].r - node[p << 1].l + 1);
		node[p << 1 | 1].v += node[p].t * (node[p << 1 | 1].r - node[p << 1 | 1].l + 1);
		node[p].t = 0;
	}
	return;
}
void segpd(int p, int l, int r, int k)
{
	if((node[p].r <= r) && (node[p].l >= l))
	{
		node[p].t += k;
		node[p].v += k * (node[p].r - node[p].l + 1);
		return;
	}
	if((node[p].r < l) || (node[p].l > r))return;
	tag(p);
	int mid = (node[p].r + node[p].l) >> 1;
	if(mid >= l)segpd(p << 1, l, r, k);
	if(mid < r)segpd(p << 1 | 1, l, r, k);
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
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d",&op);
		if(op == 1)
		{
			int x, y, k;
			scanf("%d%d%d",&x,&y,&k);
			segpd(1, x, y, k);
		}
		else if(op == 2)
		{
			int x, y;
			scanf("%d%d",&x,&y);
			printf("%lld\n", segsum(1, x, y));
		}
	}
}
