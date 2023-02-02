#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, m;
ll a[N];
struct SegTree
{
	int l, r;
	ll len;
	ll maxn, minn;
	ll sum, tag;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
	tr[p].minn = min(tr[p << 1].minn, tr[p << 1 | 1].minn);
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void addtag(int p, ll v)
{
	tr[p].maxn += v, tr[p].minn += v;
	tr[p].sum += tr[p].len * v;
	tr[p].tag += v;
}
void pushdown(int p)
{
	addtag(p << 1, tr[p].tag);
	addtag(p << 1 | 1, tr[p].tag);
	tr[p].tag = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].len = r - l + 1;
	if(l == r)
	{
		tr[p].maxn = tr[p].minn = tr[p].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, ll k)
{
	if(l <= tr[p].l && tr[p].r <= r)
	{
		addtag(p, k);
		return;
	}
	if(tr[p].tag)pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
void segsqrt(int p, int l, int r)
{
	if(l <= tr[p].l && tr[p].r <= r)
	{
		ll nmax = sqrt(tr[p].maxn), nmin = sqrt(tr[p].minn);
		if(tr[p].maxn - nmax == tr[p].minn - nmin)
		{
			addtag(p, nmax - tr[p].maxn);
			return;
		}
	}
	if(tr[p].tag)pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segsqrt(p << 1, l, r);
	if(r > mid)segsqrt(p << 1 | 1, l, r);
	pushup(p);
}
ll segsum(int p, int l, int r)
{
	if(l <= tr[p].l && tr[p].r <= r)return tr[p].sum;
	if(tr[p].tag)pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	build(1, 1, n);
	while(m--)
	{
		int op, l, r, k;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			scanf("%d", &k);
			segadd(1, l, r, k);
		}
		else if(op == 2)
		{
			segsqrt(1, l, r);
		}
		else if(op == 3)
		{
			ll res = segsum(1, l, r);
			printf("%lld\n", res);
		}
	}
	return 0;
}
