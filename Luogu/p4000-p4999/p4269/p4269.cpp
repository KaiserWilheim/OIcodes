#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int mod = 1e9 + 7;
struct SegTree
{
	int l, r;
	int ms, ml, mr;
	int val;
}tr[N << 3];
void pushup(int p)
{
	int len;
	tr[p].val = tr[p << 1].val + tr[p << 1 | 1].val;
	tr[p].ms = tr[p].ml = tr[p].mr = 0;
	tr[p].ml = max(tr[p].ml, tr[p << 1].ml);
	len = tr[p << 1].r - tr[p << 1].l + 1;
	if(tr[p << 1].ms == len)
		tr[p].ml = max(tr[p].ml, len + tr[p << 1 | 1].ml);
	tr[p].mr = max(tr[p].mr, tr[p << 1 | 1].mr);
	len = tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1;
	if(tr[p << 1 | 1].ms == len)
		tr[p].mr = max(tr[p].mr, len + tr[p << 1].mr);
	tr[p].ms = max(tr[p].ms, tr[p << 1].ms);
	tr[p].ms = max(tr[p].ms, tr[p << 1 | 1].ms);
	tr[p].ms = max(tr[p].ms, tr[p << 1].mr + tr[p << 1 | 1].ml);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].ms = tr[p].ml = tr[p].mr = 1;
		tr[p].val = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segchg(int p, int pos)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].ms = tr[p].ml = tr[p].mr = tr[p].val = 0;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos);
	else segchg(p << 1 | 1, pos);
	pushup(p);
}
struct Snow
{
	int id, step, dep;
	bool operator < (const Snow &a)const
	{
		return dep == a.dep ? step < a.step : dep < a.dep;
	}
}a[N << 1];
int n, m;
bool ans[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = { i,0,x };
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		a[i + n] = { i,v,u };
	}
	sort(a + 1, a + 1 + n + m);
	build(1, 1, n);
	for(int i = 1; i <= n + m; i++)
	{
		if(a[i].step == 0)segchg(1, a[i].id);
		else ans[a[i].id] = tr[1].ms < a[i].step;
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}