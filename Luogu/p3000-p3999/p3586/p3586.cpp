#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
ll a[N];
struct SegTree
{
	int l, r;
	int ls, rs;
	ll sum;
	ll tot;
}tr[N << 3];
int idx;
void segadd(int p, int pos, ll k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].sum += k;
		tr[p].tot = tr[p].sum * tr[p].l;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)
	{
		if(!tr[p].ls)
		{
			tr[p].ls = ++idx;
			tr[tr[p].ls].l = tr[p].l;
			tr[tr[p].ls].r = mid;
		}
		segadd(tr[p].ls, pos, k);
	}
	else if(pos > mid)
	{
		if(!tr[p].rs)
		{
			tr[p].rs = ++idx;
			tr[tr[p].rs].l = mid + 1;
			tr[tr[p].rs].r = tr[p].r;
		}
		segadd(tr[p].rs, pos, k);
	}
	tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum;
	tr[p].tot = tr[tr[p].ls].tot + tr[tr[p].rs].tot;
	return;
}

ll segsum(int p, int l, int r)
{
	if(!p)return 0;
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid)res += segsum(tr[p].ls, l, r);
	if(r > mid)res += segsum(tr[p].rs, l, r);
	return res;
}
ll segtot(int p, int l, int r)
{
	if(!p)return 0;
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].tot;
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid)res += segtot(tr[p].ls, l, r);
	if(r > mid)res += segtot(tr[p].rs, l, r);
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	int maxn = 0;
	tr[++idx] = { 0,100000001,0,0,0,0 };
	while(m--)
	{
		string op;
		int x, k;
		cin >> op;
		scanf("%d%d", &x, &k);
		if(op[0] == 'U')
		{
			if(k > 0)
			{
				segadd(1, k, 1);
			}
			if(a[x] > 0)
			{
				segadd(1, a[x], -1);
			}
			a[x] = k;
			maxn = max(maxn, k);
		}
		else if(op[0] == 'Z')
		{
			ll pos = segsum(1, 1, maxn), cnt = segsum(1, 1, k);
			if(pos < x)
			{
				puts("NIE");
				continue;
			}
			if(pos - cnt >= x)
			{
				puts("TAK");
				continue;
			}
			ll tot = segtot(1, 1, k);
			if(tot >= (x + cnt - pos) * k)
			{
				puts("TAK");
			}
			else
			{
				puts("NIE");
			}
		}
	}
	return 0;
}
