#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll INF = 1e18 + 1;
struct SegTree
{
	int l, r;
	ll sum;
	ll mod, add;
}tr[N << 3];
ll a[N];

void pushup(int p)
{
	tr[p].sum = max(tr[p << 1].sum, tr[p << 1 | 1].sum);
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.mod != -INF)
	{
		left.sum = root.mod;
		rght.sum = root.mod;
		left.mod = root.mod, left.add = 0;
		rght.mod = root.mod, rght.add = 0;
		root.mod = -INF;
	}
	if(root.add)
	{
		if(left.mod != -INF)left.mod += root.add;
		else left.add += root.add;
		left.sum += root.add;
		if(rght.mod != -INF)rght.mod += root.add;
		else rght.add += root.add;
		rght.sum += root.add;
		root.add = 0;
	}
	pushup(p);
}

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].mod = -INF;
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
		if(tr[p].mod != -INF)tr[p].mod += k;
		else tr[p].add += k;
		tr[p].sum += k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
void segmod(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].mod = k;
		tr[p].add = 0;
		tr[p].sum = k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segmod(p << 1, l, r, k);
	if(r > mid)segmod(p << 1 | 1, l, r, k);
	pushup(p);
}
ll segmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = -INF;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
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
		int op, l, r, k;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			scanf("%d", &k);
			segmod(1, l, r, k);
		}
		else if(op == 2)
		{
			scanf("%d", &k);
			segadd(1, l, r, k);
		}
		else if(op == 3)
		{
			printf("%lld\n", segmax(1, l, r));
		}
	}
	return 0;
}
