#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll mod = 998244353;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
int n, q;
ll A, B;
ll ta, tb, T;
ll pa[N], pb[N], P[N];
struct SegTree
{
	int l, r;
	ll sumk, sumb;
	ll rghk, rghb;
	ll sump;
	SegTree()
	{
		l = r = 0;
		sumk = sumb = 0;
		rghk = rghb = 0;
		sump = 0;
	}
	friend SegTree operator + (const SegTree &left, const SegTree &rght)
	{
		SegTree root;
		root.l = left.l, root.r = rght.r;
		root.rghk = rght.rghk * left.rghk % mod;
		root.rghb = (rght.rghk * left.rghb + rght.rghb) % mod;
		root.sumk = (rght.sumk * left.rghk + left.sumk) % mod;
		root.sumb = (rght.sumk * left.rghb + rght.sumb + left.sumb) % mod;
		root.sump = (left.sump + rght.sump) % mod;
		return root;
	}
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].rghk = (P[l] * (1 - T) % mod + mod + T) % mod;
		tr[p].sumk = tr[p].sumb = tr[p].rghb = tr[p].sump = P[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segchg(int p, int pos, ll k)
{
	if(tr[p].l == tr[p].r)
	{
		P[pos] = k;
		tr[p].rghk = (k * (1 - T) % mod + mod + T) % mod;
		tr[p].sumk = tr[p].sumb = tr[p].rghb = tr[p].sump = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos, k);
	else segchg(p << 1 | 1, pos, k);
	pushup(p);
}
SegTree segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p];
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l > mid)return segsum(p << 1 | 1, l, r);
	else if(r <= mid)return segsum(p << 1, l, r);
	else return segsum(p << 1, l, r) + segsum(p << 1 | 1, l, r);
}
namespace SUB
{
#define lowbit(x) ((x)&(-(x)))
	ll tr[N];
	void segadd(int x, ll c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr[i] = (tr[i] + c) % mod;
	}
	ll segsum(int x)
	{
		ll res = 0;
		for(int i = x; i; i -= lowbit(i))
			res = (res + tr[i]) % mod;
		return res;
	}
	ll query(int l, int r)
	{
		return ((segsum(r) - segsum(l - 1)) % mod + mod) % mod;
	}
	void solve()
	{
		for(int i = 1; i <= n; i++)
			segadd(i, P[i]);
		for(int _i = 1; _i <= q; _i++)
		{
			int op;
			scanf("%d", &op);
			if(op == 0)
			{
				int x;
				ll wa, wb;
				scanf("%d%lld%lld", &x, &wa, &wb);
				int ls = P[x];
				P[x] = wa * qpow(wb, mod - 2) % mod;
				segadd(x, (P[x] - ls + mod) % mod);
			}
			else
			{
				int l, r;
				scanf("%d%d", &l, &r);
				ll res = query(l, r) * A % mod;
				printf("%lld\n", res);
			}
		}
	}
}
int main()
{
	int id;
	scanf("%d", &id);
	scanf("%d%d%lld%lld%lld%lld", &n, &q, &ta, &tb, &A, &B);
	T = ta * qpow(tb, mod - 2) % mod;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &pa[i], &pb[i]);
		P[i] = pa[i] * qpow(pb[i], mod - 2) % mod;
	}
	if(B == 0)
	{
		SUB::solve();
		return 0;
	}
	build(1, 1, n);
	for(int _i = 1; _i <= q; _i++)
	{
		int op;
		scanf("%d", &op);
		if(op == 0)
		{
			int x;
			ll wa, wb;
			scanf("%d%lld%lld", &x, &wa, &wb);
			ll w = wa * qpow(wb, mod - 2) % mod;
			segchg(1, x, w);
		}
		else
		{
			int l, r;
			scanf("%d%d", &l, &r);
			SegTree res = segsum(1, l, r);
			ll ans = (A * res.sump + B * res.sumb) % mod;
			printf("%lld\n", ans);
		}
	}
	return 0;
}