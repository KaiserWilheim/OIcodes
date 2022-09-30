#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
struct SegTree
{
	int l, r;
	pair<int, int> max;
};
int n;
const pair<int, int>minn = make_pair(INT_MIN, INT_MIN);
pair<int, int>f[N];
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].max = minn;
	f[p] = minn;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int pos, pair<int, int>k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].max = max(tr[p].max, k);
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segadd(p << 1, pos, k);
	else segadd(p << 1 | 1, pos, k);
	pushup(p);
}
pair<int, int>segsum(int p, int l, int r)
{
	if(r < l)return minn;
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].max;
	pair<int, int>res = minn;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = max(res, segsum(p << 1, l, r));
	if(r > mid)res = max(res, segsum(p << 1 | 1, l, r));
	return res;
}
int a[N], tmp[N];
int ans = 0;
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	sort(tmp + 1, tmp + 1 + n);
	int cnt = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(tmp + 1, tmp + 1 + cnt, a[i]) - tmp;
	build(1, 1, n);
	for(int i = 1; i <= n; i++)
	{
		pair<int, int>now = segsum(1, 1, a[i]);
		f[i] = make_pair(1, i);
		f[i] = max(f[i], make_pair(now.first + 1, now.second));
		ans = max(ans, f[i].first);
		segadd(1, a[i], f[i]);
	}
	printf("%d ", ans);
	int num = INT_MAX;
	for(int i = 1; i <= n; i++)
		if(f[i].first == ans)
			num = min(num, n - ans - (n - i + f[i].second - 1));
	printf("%d\n", num);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ans = 0;
		solve();
	}
	return 0;
}