#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int a[N];
struct SegTree
{
	int l, r;
	int maxn;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].maxn = 0;
	if(l == r)
	{
		tr[p].maxn = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segchg(int p, int pos, int k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].maxn = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos, k);
	else if(pos > mid)segchg(p << 1 | 1, pos, k);
	pushup(p);
}
int segmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].maxn;
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
int getposl(int p, int l, int r, int k)
{
	if(tr[p].maxn <= k)return n + 1;
	if(tr[p].l == tr[p].r)return tr[p].l;
	if(tr[p].l >= l && tr[p].r <= r)
	{
		if(tr[p << 1].maxn <= k)return getposl(p << 1 | 1, l, r, k);
		else return getposl(p << 1, l, r, k);
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = n + 1;
	if(l <= mid)res = min(res, getposl(p << 1, l, r, k));
	if(r > mid)res = min(res, getposl(p << 1 | 1, l, r, k));
	return res;
}
int getposr(int p, int l, int r, int k)
{
	if(tr[p].maxn <= k)return 0;
	if(tr[p].l == tr[p].r)return tr[p].l;
	if(tr[p].l >= l && tr[p].r <= r)
	{
		if(tr[p << 1 | 1].maxn <= k)return getposr(p << 1, l, r, k);
		else return getposr(p << 1 | 1, l, r, k);
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(r > mid)res = max(res, getposr(p << 1 | 1, l, r, k));
	if(l <= mid)res = max(res, getposr(p << 1, l, r, k));
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		string s;
		int p, k;
		cin >> s;
		if(s == "U")
		{
			scanf("%d%d", &p, &k);
			segchg(1, p, k);
			a[p] = k;
		}
		else
		{
			bool flag = (s == "R");
			scanf("%d", &p);
			int maxr = segmax(1, p + 1, n);
			int maxl = segmax(1, 1, p - 1);
			if(maxl < a[p] && maxr < a[p])
			{
				printf("%d\n", p);
			}
			else if(maxl > a[p] && maxr < a[p])
			{
				if(flag)
				{
					printf("%d\n", p);
				}
				else
				{
					p = getposr(1, 1, p - 1, a[p]);
					printf("%d\n", p);
				}
			}
			else if(maxr > a[p] && maxl < a[p])
			{
				if(!flag)
				{
					printf("%d\n", p);
				}
				else
				{
					p = getposl(1, p + 1, n, a[p]);
					printf("%d\n", p);
				}
			}
			else
			{
				if(maxl < maxr)
				{
					int pl = getposr(1, 1, p - 1, maxl);
					p = getposl(1, p + 1, n, maxl);
					printf("%d\n", p);
				}
				else
				{
					int pr = getposl(1, p + 1, n, maxr);
					p = getposr(1, 1, p - 1, maxr);
					printf("%d\n", p);
				}
			}
		}
	}
	return 0;
}