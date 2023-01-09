#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
ll a[N];
struct SegTree
{
	int l, r;
	ll sum;
	ll maxn, maxs, cmax;
	ll hmaxn, hmaxs;
	ll addn, adds;
	ll haddn, hadds;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].hmaxn = max(tr[p << 1].hmaxn, tr[p << 1 | 1].hmaxn);
	if(tr[p << 1].maxn > tr[p << 1 | 1].maxn)
	{
		tr[p].maxn = tr[p << 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxs, tr[p << 1 | 1].maxn);
		tr[p].cmax = tr[p << 1].cmax;
	}
	else if(tr[p << 1].maxn < tr[p << 1 | 1].maxn)
	{
		tr[p].maxn = tr[p << 1 | 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxn, tr[p << 1 | 1].maxs);
		tr[p].cmax = tr[p << 1 | 1].cmax;
	}
	else
	{
		tr[p].maxn = tr[p << 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxs, tr[p << 1 | 1].maxs);
		tr[p].cmax = tr[p << 1].cmax + tr[p << 1 | 1].cmax;
	}
}
void add(int p, ll vn, ll hvn, ll vs, ll hvs)
{
	tr[p].hmaxn = max(tr[p].hmaxn, tr[p].maxn + hvn);
	tr[p].haddn = max(tr[p].haddn, tr[p].addn + hvn);
	tr[p].hadds = max(tr[p].hadds, tr[p].adds + hvs);
	tr[p].sum += 1ll * vn * tr[p].cmax;
	tr[p].sum += 1ll * vs * (tr[p].r - tr[p].l + 1 - tr[p].cmax);
	tr[p].addn += vn, tr[p].adds += vs;
	tr[p].maxn += vn, tr[p].maxs += vs;
}
void pushdown(int p)
{
	int maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
	if(maxn == tr[p << 1].maxn)
		add(p << 1, tr[p].addn, tr[p].haddn, tr[p].adds, tr[p].hadds);
	else add(p << 1, tr[p].adds, tr[p].hadds, tr[p].adds, tr[p].hadds);
	if(maxn == tr[p << 1 | 1].maxn)
		add(p << 1 | 1, tr[p].addn, tr[p].haddn, tr[p].adds, tr[p].hadds);
	else add(p << 1 | 1, tr[p].adds, tr[p].hadds, tr[p].adds, tr[p].hadds);
	tr[p].addn = tr[p].haddn = tr[p].adds = tr[p].hadds = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = a[l];
		tr[p].maxn = tr[p].hmaxn = a[l];
		tr[p].cmax = 1;
		tr[p].maxs = tr[p].hmaxs = -1e9;
		tr[p].addn = tr[p].haddn = 0;
		tr[p].adds = tr[p].hadds = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, ll k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		add(p, k, k, k, k);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
void segmin(int p, int l, int r, ll k)
{
	if(k >= tr[p].maxn)return;
	if(tr[p].l >= l && tr[p].r <= r && k > tr[p].maxs)
	{
		add(p, k - tr[p].maxn, k - tr[p].maxn, 0, 0);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segmin(p << 1, l, r, k);
	if(r > mid)segmin(p << 1 | 1, l, r, k);
	pushup(p);
}
ll segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
ll segmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].maxn;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = -1e9;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
ll seghmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].hmaxn;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = -1e9;
	if(l <= mid)res = max(res, seghmax(p << 1, l, r));
	if(r > mid)res = max(res, seghmax(p << 1 | 1, l, r));
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
		int op, l, r;
		ll k;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			scanf("%lld", &k);
			segadd(1, l, r, k);
		}
		else if(op == 2)
		{
			scanf("%lld", &k);
			segmin(1, l, r, k);
		}
		else if(op == 3)
		{
			ll res = segsum(1, l, r);
			printf("%lld\n", res);
		}
		else if(op == 4)
		{
			ll res = segmax(1, l, r);
			printf("%lld\n", res);
		}
		else if(op == 5)
		{
			ll res = seghmax(1, l, r);
			printf("%lld\n", res);
		}
		else puts("Youwike AK IOI!");
	}
	return 0;
}
