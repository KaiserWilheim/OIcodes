#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int a[N];
struct SegTree
{
	int l, r;
	ll sum;
	int maxn, maxs, cmax;
	int addn, adds;
	int cnt;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].cnt = tr[p << 1].cnt + tr[p << 1 | 1].cnt;
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
void add(int p, int vn, int vs)
{
	tr[p].sum += 1ll * vn * tr[p].cmax;
	tr[p].sum += 1ll * vs * (tr[p].cnt - tr[p].cmax);
	tr[p].addn += vn, tr[p].adds += vs;
	tr[p].maxn += vn, tr[p].maxs += vs;
}
void pushdown(int p)
{
	int maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
	if(maxn == tr[p << 1].maxn)
		add(p << 1, tr[p].addn, tr[p].adds);
	else add(p << 1, tr[p].adds, tr[p].adds);
	if(maxn == tr[p << 1 | 1].maxn)
		add(p << 1 | 1, tr[p].addn, tr[p].adds);
	else add(p << 1 | 1, tr[p].adds, tr[p].adds);
	tr[p].addn = tr[p].adds = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].addn = tr[p].adds = 0;
	if(l == r)
	{
		tr[p].sum = 0;
		tr[p].cmax = 0;
		tr[p].maxn = tr[p].maxs = 0;
		tr[p].cnt = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
int segadd(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		add(p, k, k);
		return tr[p].cnt;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res += segadd(p << 1, l, r, k);
	if(r > mid)res += segadd(p << 1 | 1, l, r, k);
	pushup(p);
	return res;
}
void segmod(int p, int pos, int k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].sum = k;
		tr[p].maxn = k;
		tr[p].cmax = 1;
		tr[p].cnt = 1;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segmod(p << 1, pos, k);
	if(pos > mid)segmod(p << 1 | 1, pos, k);
	pushup(p);
}
void segmin(int p, int l, int r, int k)
{
	if(l > r)return;
	if(k >= tr[p].maxn)return;
	if(tr[p].l >= l && tr[p].r <= r && k > tr[p].maxs)
	{
		add(p, k - tr[p].maxn, 0);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segmin(p << 1, l, r, k);
	if(r > mid)segmin(p << 1 | 1, l, r, k);
	pushup(p);
}
int pos[N];
ll res[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}
	for(int _i = 1; _i <= 2; _i++)
	{
		build(1, 1, n);
		for(int i = 1; i <= n; i++)
		{
			int x = segadd(1, pos[i] + 1, n, 1);
			segmod(1, pos[i], i + 1);
			segmin(1, 1, pos[i] - 1, i - x);
			res[i] += tr[1].sum;
		}
		for(int i = 1; i <= n; i++)
			pos[i] = n - pos[i] + 1;
	}
	for(int i = 1; i <= n; i++)
		printf("%lld\n", res[i] - 1ll * i * (i + 2));
	return 0;
}
