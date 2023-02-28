#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pdi pair<double,int>
const int N = 40010, M = 100010;
const double eps = 1e-9;
const int mod1 = 39989, mod2 = 1e9 + 1;
int n;
struct Line
{
	double k, b;
};
Line p[M];
int idx;
void add(int x1, int y1, int x2, int y2)
{
	idx++;
	if(x1 == x2)p[idx].k = 0, p[idx].b = max(y1, y2);
	else p[idx].k = 1.0 * (y2 - y1) / (x2 - x1), p[idx].b = y1 - p[idx].k * x1;
}
double calc(int id, int x) { return p[id].k * x + p[id].b; }
int cmp(double x, double y)
{
	if(x - y > eps)return 1;
	if(y - x > eps)return -1;
	return 0;
}
struct SegTree
{
	int l, r;
	int id;
};
SegTree tr[N << 3];
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].id = 0;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void pushtag(int p, int u)
{
	int &v = tr[p].id, mid = (tr[p].l + tr[p].r) >> 1;
	if(cmp(calc(u, mid), calc(v, mid)) == 1)swap(u, v);
	int bl = cmp(calc(u, tr[p].l), calc(v, tr[p].l)),
		br = cmp(calc(u, tr[p].r), calc(v, tr[p].r));
	if(bl == 1 || (!bl && u < v))pushtag(p << 1, u);
	if(br == 1 || (!br && u < v))pushtag(p << 1 | 1, u);
}
void update(int p, int l, int r, int u)
{
	if(l <= tr[p].l && tr[p].r <= r)
	{
		pushtag(p, u);
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)update(p << 1, l, r, u);
	if(r > mid)update(p << 1 | 1, l, r, u);
}
pdi max(pdi x, pdi y)
{
	if(cmp(x.first, y.first) == -1)return y;
	if(cmp(x.first, y.first) == 1)return x;
	return x.second < y.second ? x : y;
}
pdi query(int p, int pos)
{
	if(pos > tr[p].r || pos < tr[p].l)return make_pair(0.0, 0);
	int mid = (tr[p].l + tr[p].r) >> 1;
	double res = calc(tr[p].id, pos);
	if(tr[p].l == tr[p].r)return make_pair(res, tr[p].id);
	return max(make_pair(res, tr[p].id), max(query(p << 1, pos), query(p << 1 | 1, pos)));
}
int main()
{
	int lans = 0;
	scanf("%d", &n);
	build(1, 1, 40000);
	while(n--)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x1 = (x1 + lans - 1 + mod1) % mod1 + 1;
			x2 = (x2 + lans - 1 + mod1) % mod1 + 1;
			y1 = (y1 + lans - 1 + mod2) % mod2 + 1;
			y2 = (y2 + lans - 1 + mod2) % mod2 + 1;
			if(x1 > x2)swap(x1, x2), swap(y1, y2);
			add(x1, y1, x2, y2);
			update(1, x1, x2, idx);
		}
		else
		{
			int x;
			scanf("%d", &x);
			x = (x + lans - 1 + mod1) % mod1 + 1;
			lans = query(1, x).second;
			printf("%d\n", lans);
		}
	}
	return 0;
}
