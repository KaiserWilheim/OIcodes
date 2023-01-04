#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
double x[N], y[N];
double calc(double x)
{
	return x * (x + 1) * (2 * x + 1) / 6;
}
struct Ret
{
	double xx, xy, x, y;
	friend Ret operator + (const Ret &a, const Ret &b)
	{
		return { a.xx + b.xx,a.xy + b.xy,a.x + b.x,a.y + b.y };
	}
};
struct SegTree
{
	int l, r;
	double xx, xy, x, y;
	double s, t;
	bool c;
}tr[N << 3];
void modadd(int p, double s, double t)
{
	double len = double(tr[p].r - tr[p].l + 1);
	tr[p].xx += s * s * len + 2 * s * tr[p].x;
	tr[p].xy += s * t * len + s * tr[p].y + t * tr[p].x;
	tr[p].x += s * len;
	tr[p].y += t * len;
	tr[p].s += s;
	tr[p].t += t;
}
void modchg(int p)
{
	double l = double(tr[p].l), r = double(tr[p].r);
	tr[p].xx = tr[p].xy = calc(r) - calc(l - 1);
	tr[p].x = tr[p].y = (r - l + 1) * (l + r) / 2;
	tr[p].c = true;
	tr[p].s = tr[p].t = 0;
}
void pushup(int p)
{
	tr[p].xx = tr[p << 1].xx + tr[p << 1 | 1].xx;
	tr[p].x = tr[p << 1].x + tr[p << 1 | 1].x;
	tr[p].y = tr[p << 1].y + tr[p << 1 | 1].y;
	tr[p].xy = tr[p << 1].xy + tr[p << 1 | 1].xy;
}
void pushdown(int p)
{
	if(tr[p].c)
	{
		modchg(p << 1), modchg(p << 1 | 1);
	}
	modadd(p << 1, tr[p].s, tr[p].t);
	modadd(p << 1 | 1, tr[p].s, tr[p].t);
	tr[p].c = false;
	tr[p].s = tr[p].t = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].xx = x[l] * x[r];
		tr[p].x = x[l];
		tr[p].y = y[l];
		tr[p].xy = x[l] * y[r];
		tr[p].s = tr[p].t = 0;
		tr[p].c = false;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, double s, double t)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		modadd(p, s, t);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, s, t);
	if(r > mid)segadd(p << 1 | 1, l, r, s, t);
	pushup(p);
}
void segchg(int p, int l, int r, double s, double t)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		modchg(p);
		modadd(p, s, t);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segchg(p << 1, l, r, s, t);
	if(r > mid)segchg(p << 1 | 1, l, r, s, t);
	pushup(p);
}
Ret segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return { tr[p].xx,tr[p].xy,tr[p].x,tr[p].y };
	pushdown(p);
	Ret res = { 0,0,0,0 };
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = res + segsum(p << 1, l, r);
	if(r > mid)res = res + segsum(p << 1 | 1, l, r);
	return res;
}
double ans(double l, double r)
{
	Ret res = segsum(1, l, r);
	double len = r - l + 1;
	return (res.xy - res.x * res.y / len) / (res.xx - res.x * res.x / len);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lf", &x[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lf", &y[i]);
	build(1, 1, n);
	while(m--)
	{
		int op, l, r;
		double s, t;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			printf("%.6lf\n", ans(l, r));
		}
		else if(op == 2)
		{
			scanf("%lf%lf", &s, &t);
			segadd(1, l, r, s, t);
		}
		else if(op == 3)
		{
			scanf("%lf%lf", &s, &t);
			segchg(1, l, r, s, t);
		}
	}
	return 0;
}
