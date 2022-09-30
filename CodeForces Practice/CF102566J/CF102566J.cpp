#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
struct Query
{
	int type;
	int l, r, t, b;
	ll val;
}qry[N];
ll ans[N];
int n, m;
ll a[11][N], sum[11][N], tmp[11][N];
struct SegTree
{
	int l, r;
	ll prf, suf;
	ll sum, ms;
	friend SegTree operator + (const SegTree &lhs, const SegTree &rhs)
	{
		SegTree res;
		res.l = lhs.l, res.r = rhs.r;
		res.sum = lhs.sum + rhs.sum;
		res.prf = max(lhs.prf, lhs.sum + rhs.prf);
		res.suf = max(rhs.suf, lhs.suf + rhs.sum);
		res.ms = max(max(lhs.ms, rhs.ms), lhs.suf + rhs.prf);
		return res;
	}
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
void build(int p, int l, int r, int t, int b)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].ms = tr[p].sum = 0;
	tr[p].prf = tr[p].suf = 0;
	if(l == r)
	{
		tr[p].sum = sum[b][l] - sum[t - 1][l];
		tr[p].ms = tr[p].sum;
		tr[p].prf = tr[p].sum;
		tr[p].suf = tr[p].sum;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid, t, b);
	build(p << 1 | 1, mid + 1, r, t, b);
	pushup(p);
}
void segadd(int p, int pos, ll k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].sum += k;
		tr[p].ms = tr[p].sum;
		tr[p].prf = tr[p].sum;
		tr[p].suf = tr[p].sum;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segadd(p << 1, pos, k);
	else segadd(p << 1 | 1, pos, k);
	pushup(p);
}
SegTree segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p];
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(r <= mid)return segsum(p << 1, l, r);
	if(l > mid)return segsum(p << 1 | 1, l, r);
	return segsum(p << 1, l, r) + segsum(p << 1 | 1, l, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			sum[i][j] = sum[i - 1][j] + a[i][j];
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int op, l, r, t, b;
		ll v;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			scanf("%lld", &v);
			qry[i] = { 1,l,r,0,0,v };
		}
		else
		{
			scanf("%d%d", &t, &b);
			qry[i] = { 2,l,r,t,b,0 };
		}
		ans[i] = -1e18;
	}
	for(int t = 1; t <= n; t++)
	{
		for(int b = t; b <= n; b++)
		{
			build(1, 1, m, t, b);
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= m; j++)
					tmp[i][j] = a[i][j];
			for(int i = 1; i <= q; i++)
			{
				if(qry[i].type == 2)
				{
					if(qry[i].l > t || qry[i].t < b)continue;
					SegTree res = segsum(1, qry[i].r, qry[i].b);
					ans[i] = max(ans[i], res.ms);
				}
				else
				{
					if(qry[i].l > b || qry[i].l < t)continue;
					segadd(1, qry[i].r, qry[i].val - tmp[qry[i].l][qry[i].r]);
					tmp[qry[i].l][qry[i].r] = qry[i].val;
				}
			}
		}
	}
	for(int i = 1; i <= q; i++)
	{
		if(qry[i].type == 2)
			printf("%lld\n", ans[i]);
	}
	return 0;
}