#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 1000010;
int n, m;
struct Point
{
	int x[2];
	ll w;
	Point() {}
	Point(int _x, int _y, ll _w)
	{
		x[0] = _x, x[1] = _y, w = _w;
	}
};
const double alpha = 0.75;
struct Node
{
	int ls, rs;
	int l[2], r[2];
	ll sum, sz;
	Point p;
};
Node tr[N];
int rt, idx = 0;
int rec[N], tt;
int newnode()
{
	if(tt)return rec[tt--];
	else return ++idx;
}
void pushup(int p)
{
	tr[p].l[0] = tr[p].r[0] = tr[p].p.x[0];
	tr[p].l[1] = tr[p].r[1] = tr[p].p.x[1];
	tr[p].sum = tr[p].p.w;
	tr[p].sz = 1;
	if(tr[p].ls)
	{
		tr[p].l[0] = min(tr[p].l[0], tr[tr[p].ls].l[0]);
		tr[p].l[1] = min(tr[p].l[1], tr[tr[p].ls].l[1]);
		tr[p].r[0] = max(tr[p].r[0], tr[tr[p].ls].r[0]);
		tr[p].r[1] = max(tr[p].r[1], tr[tr[p].ls].r[1]);
		tr[p].sum += tr[tr[p].ls].sum;
		tr[p].sz += tr[tr[p].ls].sz;
	}
	if(tr[p].rs)
	{
		tr[p].l[0] = min(tr[p].l[0], tr[tr[p].rs].l[0]);
		tr[p].l[1] = min(tr[p].l[1], tr[tr[p].rs].l[1]);
		tr[p].r[0] = max(tr[p].r[0], tr[tr[p].rs].r[0]);
		tr[p].r[1] = max(tr[p].r[1], tr[tr[p].rs].r[1]);
		tr[p].sum += tr[tr[p].rs].sum;
		tr[p].sz += tr[tr[p].rs].sz;
	}
}
bool cmp0(Point a, Point b) { return a.x[0] < b.x[0]; }
bool cmp1(Point a, Point b) { return a.x[1] < b.x[1]; }
Point ldr[N];
int ldc;
int build(int l, int r, int k)
{
	if(l > r)return 0;
	int mid = (l + r) >> 1;
	int p = newnode();
	nth_element(ldr + l, ldr + mid, ldr + r + 1, k ? cmp1 : cmp0);
	tr[p].p = ldr[mid];
	tr[p].ls = build(l, mid - 1, k ^ 1);
	tr[p].rs = build(mid + 1, r, k ^ 1);
	pushup(p);
	return p;
}
ll a, b, c;
bool chq(ll x, ll y)
{
	return a * x + b * y < c;
}
int count(int p)
{
	int res = 0;
	res += chq(tr[p].l[0], tr[p].l[1]);
	res += chq(tr[p].r[0], tr[p].r[1]);
	res += chq(tr[p].l[0], tr[p].r[1]);
	res += chq(tr[p].r[0], tr[p].l[1]);
	return res;
}
ll query(int p)
{
	if(!p)return 0;
	int cnt = count(p);
	if(cnt == 4)return tr[p].sum;
	else
	{
		ll res = 0;
		if(chq(tr[p].p.x[0], tr[p].p.x[1]))res += tr[p].p.w;
		res += query(tr[p].ls);
		res += query(tr[p].rs);
		return res;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%lld", &ldr[i].x[0], &ldr[i].x[1], &ldr[i].w);
	ldc = 0;
	rt = build(1, n, 0);
	for(int i = 1; i <= m; i++)
	{
		scanf("%lld%lld%lld", &a, &b, &c);
		ll res = query(rt);
		printf("%lld\n", res);
	}
	return 0;
}
