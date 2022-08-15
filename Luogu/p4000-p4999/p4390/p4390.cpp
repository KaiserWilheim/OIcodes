#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, k;
struct Point
{
	int x[2], w;
	Point() {};
	Point(int _x, int _y, int _w)
	{
		x[0] = _x, x[1] = _y, w = _w;
	}
	friend bool operator == (const Point &a, const Point &b)
	{
		return (a.x[0] == b.x[0]) && (a.x[1] == b.x[1]);
	}
};
const double alpha = 0.75;
struct KDT
{
	int ls, rs;
	int l[2], r[2];//[l,u],[r,d]
	int sum, sz;
	Point p;
}tr[N];
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

bool cmp0(Point a, Point b)
{
	return a.x[0] < b.x[0];
}
bool cmp1(Point a, Point b)
{
	return a.x[1] < b.x[1];
}
bool canrbu(int p)
{
	return (1.0 * max(tr[tr[p].ls].sz, tr[tr[p].rs].sz)) >= (alpha * tr[p].sz);
}
Point ldr[N];
int ldc;
void rbuunf(int p)
{
	if(!p)return;
	rbuunf(tr[p].ls);
	if(tr[p].p.w)
	{
		ldr[++ldc] = tr[p].p;
		rec[++tt] = p;
	}
	rbuunf(tr[p].rs);
}
int rbubld(int l, int r, int k)
{
	if(l > r)return 0;
	int mid = (l + r) >> 1;
	int p = newnode();
	nth_element(ldr + l, ldr + mid, ldr + r + 1, k ? cmp1 : cmp0);
	tr[p].p = ldr[mid];
	tr[p].ls = rbubld(l, mid - 1, k ^ 1);
	tr[p].rs = rbubld(mid + 1, r, k ^ 1);
	pushup(p);
	return p;
}
void rbuild(int &p, int k)
{
	ldc = 0;
	rbuunf(p);
	p = rbubld(1, ldc, k);
}

void insert(int &p, Point v, int k)
{
	if(!p)
	{
		p = newnode();
		tr[p].ls = tr[p].rs = 0;
		tr[p].p = v;
		pushup(p);
		return;
	}
	if(v.x[k] <= tr[p].p.x[k])insert(tr[p].ls, v, k ^ 1);
	else insert(tr[p].rs, v, k ^ 1);
	pushup(p);
	if(canrbu(p))rbuild(p, k);
}

inline bool inc(Point p, int x1, int y1, int x2, int y2)
{
	return (p.x[0] >= x1) && (p.x[0] <= x2) && (p.x[1] >= y1) && (p.x[1] <= y2);
}
inline bool inc(int p, int x1, int y1, int x2, int y2)
{
	return (tr[p].l[0] >= x1) && (tr[p].r[0] <= x2) && (tr[p].l[1] >= y1) && (tr[p].r[1] <= y2);
}
inline bool exc(int p, int x1, int y1, int x2, int y2)
{
	return (tr[p].l[0] > x2) || (tr[p].r[0] < x1) || (tr[p].l[1] > y2) || (tr[p].r[1] < y1);
}
int query(int p, int x1, int y1, int x2, int y2)
{
	if(!p)return 0;
	if(exc(p, x1, y1, x2, y2))return 0;
	if(inc(p, x1, y1, x2, y2))return tr[p].sum;
	int res = 0;
	if(inc(tr[p].p, x1, y1, x2, y2))res += tr[p].p.w;
	res += query(tr[p].ls, x1, y1, x2, y2);
	res += query(tr[p].rs, x1, y1, x2, y2);
	return res;
}

int main()
{
	int lastans = 0, op;
	scanf("%d%d", &lastans, &n);
	while(scanf("%d", &op), op != 3)
	{
		if(op == 1)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			insert(rt, Point(x, y, w), 0);
		}
		else if(op == 2)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			lastans = query(rt, x1, y1, x2, y2);
			printf("%d\n", lastans);
		}
	}
}
