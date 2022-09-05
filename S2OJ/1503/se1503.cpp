#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
struct Spell
{
	int t, w, id;
	bool operator < (const Spell &a)const
	{
		return t > a.t;
	}
};
Spell a[N];
struct SegTree
{
	int l, r;
	int sum;
	int maxn, minn;
}tr[N << 3];
SegTree pre;
SegTree merge(SegTree lhs, SegTree rhs)
{
	SegTree res;
	res.l = lhs.l, res.r = rhs.r;
	res.sum = lhs.sum + rhs.sum;
	res.maxn = max(lhs.maxn, lhs.sum + rhs.maxn);
	res.minn = min(lhs.minn, lhs.sum + rhs.minn);
	return res;
}
void pushup(int p)
{
	tr[p] = merge(tr[p << 1], tr[p << 1 | 1]);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = tr[p].maxn = tr[p].minn = a[l].w;
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
		tr[p].sum = tr[p].maxn = tr[p].minn = 0;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos);
	else segchg(p << 1 | 1, pos);
	pushup(p);
}
SegTree qrypfx(int p, int pos)
{
	if(pos >= tr[p].r)return tr[p];
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)return qrypfx(p << 1, pos);
	else return merge(tr[p << 1], qrypfx(p << 1 | 1, pos));
}
int query1(int p)
{
	if(tr[p].l == tr[p].r)
	{
		SegTree res = merge(pre, tr[p]);
		if(res.maxn >= m)return 0;
		else return 1;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	SegTree res = merge(pre, tr[p << 1]);
	if(res.maxn >= m)return query1(p << 1);
	pre = res;
	return query1(p << 1 | 1) + (mid - tr[p].l + 1);
}
int query2(int p)
{
	if(tr[p].l == tr[p].r)
	{
		SegTree res = merge(pre, tr[p]);
		if(res.minn <= 0)return 0;
		else return 1;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	SegTree res = merge(pre, tr[p << 1]);
	if(res.minn <= 0)return query2(p << 1);
	pre = res;
	return query2(p << 1 | 1) + (mid - tr[p].l + 1);
}
int chq()
{
	int t1, t2;
	pre.sum = pre.maxn = pre.minn = 0;
	t1 = query1(1);
	pre.sum = pre.maxn = 0, pre.minn = m + 1;
	t2 = query2(1);
	if(t1 == n + 1 && t2 == n + 1)return tr[1].sum;
	if(t1 == t2)return m;
	if(t1 > t2)
	{
		pre = qrypfx(1, t1);
		if(pre.minn < 0)return -1;
		if(t1 == n + 1)return tr[1].sum;
		else return m;
	}
	else
	{
		pre = qrypfx(1, t2);
		if(pre.maxn > m)return -1;
		else return m;
	}
}
int main()
{
	cin >> n >> m >> a[0].w;
	for(int i = n; i >= 1; i--)
	{
		string s;
		cin >> s;
		if(s == "+")a[i].w = -1;
		else a[i].w = 1;
		cin >> a[i].t;
		a[i].id = i;
	}
	for(int i = 1; i < n; i++)a[i].t -= a[i + 1].t;
	build(1, 0, n);
	int flag = chq();
	if(flag != -1)
	{
		puts("infinity");
		return 0;
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		segchg(1, a[i].id);
		while(i < n && a[i + 1].t == a[i].t)segchg(1, a[++i].id);
		flag = chq();
		if(flag != -1)
		{
			printf("%d %d\n", a[i].t - 1, flag);
			return 0;
		}
	}
	return 0;
}