#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
struct SegTree
{
	int ls, rs;
	int maxn, minn;
	ll sum;
	int sz;
};
SegTree tr[N * 21];
int rt[N], idx;
void segadd(int &p, int q, int l, int r, int k)
{
	p = ++idx;
	tr[p].ls = tr[q].ls, tr[p].rs = tr[q].rs;
	tr[p].sz = tr[q].sz + 1, tr[p].sum = tr[q].sum + k;
	if(l == r)return;
	int mid = (l + r) >> 1;
	if(k <= mid)segadd(tr[p].ls, tr[q].ls, l, mid, k);
	else segadd(tr[p].rs, tr[q].rs, mid + 1, r, k);
}
ll segsum(int p, int q, int l, int r, int f, int k)
{
	if(tr[p].sz == tr[q].sz)return 0;
	ll sz = tr[p].sz - tr[q].sz, sum = tr[p].sum - tr[q].sum;
	if(l >= k + f)return sum - ((k + f) * sz + (sz - 1) * sz / 2);
	if(r <= k + f + sz - 1)return ((k + f) * sz + (sz - 1) * sz / 2) - sum;
	int mid = (l + r) >> 1, lsz = tr[tr[p].ls].sz - tr[tr[q].ls].sz;
	return segsum(tr[p].ls, tr[q].ls, l, mid, f, k) + segsum(tr[p].rs, tr[q].rs, mid + 1, r, f + lsz, k);
}
signed main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		segadd(rt[i], rt[i - 1], 1, 1e6, x);
	}
	for(int i = 1; i <= m; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%lld\n", segsum(rt[r], rt[l - 1], 1, 1e6, 0, k));
	}
	return 0;
}
