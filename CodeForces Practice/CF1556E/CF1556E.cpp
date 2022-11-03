#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
ll a[N], b[N];
ll sum[N];
struct SegTree
{
	int l, r;
	ll minn, maxn;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].minn = min(tr[p << 1].minn, tr[p << 1 | 1].minn);
	tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].minn = tr[p].maxn = 0;
	if(l == r)
	{
		tr[p].minn = tr[p].maxn = sum[l];
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
pair<ll, ll>segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return make_pair(tr[p].maxn, tr[p].minn);
	pair<ll, ll>res = make_pair(-1e15, 1e15);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)
	{
		pair<ll, ll>tmp = segsum(p << 1, l, r);
		res.first = max(res.first, tmp.first);
		res.second = min(res.second, tmp.second);
	}
	if(r > mid)
	{
		pair<ll, ll>tmp = segsum(p << 1 | 1, l, r);
		res.first = max(res.first, tmp.first);
		res.second = min(res.second, tmp.second);
	}
	return res;
}
void solve(int l, int r)
{
	if(sum[r] - sum[l - 1] != 0)
	{
		puts("-1");
		return;
	}
	pair<ll, ll>res = segsum(1, l, r);
	if(res.first > sum[l - 1])
	{
		puts("-1");
		return;
	}
	printf("%lld\n", sum[l - 1] - res.second);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]), a[i] -= b[i];
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	build(1, 1, n);
	for(int _i = 1; _i <= m; _i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		solve(l, r);
	}
	return 0;
}
