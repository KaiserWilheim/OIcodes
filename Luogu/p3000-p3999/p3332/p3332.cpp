#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
struct SegTree
{
	int rec, tag;
	ll sum;
};
SegTree tr[N << 3];
void pushdown(int p, int l, int r)
{
	if(tr[p].rec)
	{
		tr[p << 1].tag = tr[p << 1 | 1].tag = 0;
		tr[p << 1].sum = tr[p << 1 | 1].sum = 0;
		tr[p << 1].rec = tr[p << 1 | 1].rec = 1;
		tr[p].rec = 0;
	}
	if(tr[p].tag)
	{
		int mid = (l + r) >> 1;
		tr[p << 1].tag += tr[p].tag, tr[p << 1 | 1].tag += tr[p].tag;
		tr[p << 1].sum += tr[p].tag * (mid - l + 1);
		tr[p << 1 | 1].sum += tr[p].tag * (r - mid);
		tr[p].tag = 0;
	}
}
void segadd(int p, int l, int r, int dl, int dr, int w)
{
	if(dl >= l && dr <= r)
	{
		tr[p].tag += w;
		tr[p].sum += w * (dr - dl + 1);
		return;
	}
	if(tr[p].tag || tr[p].rec)pushdown(p, dl, dr);
	int mid = (dl + dr) >> 1;
	if(l <= mid)segadd(p << 1, l, r, dl, mid, w);
	if(r > mid)segadd(p << 1 | 1, l, r, mid + 1, dr, w);
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
ll segsum(int p, int l, int r, int dl, int dr)
{
	if(dl >= l && dr <= r)return tr[p].sum;
	if(tr[p].tag || tr[p].rec)pushdown(p, dl, dr);
	int mid = (dl + dr) >> 1;
	ll res = 0;
	if(l <= mid)res += segsum(p << 1, l, r, dl, mid);
	if(r > mid)res += segsum(p << 1 | 1, l, r, mid + 1, dr);
	return res;
}
struct Query
{
	int l, r;
	int op, id;
	ll v;
};
Query q[N], ql[N], qr[N];
int ans[N];
void solve(int st, int ed, int l, int r)
{
	if(l == r)
	{
		for(int i = st; i <= ed; i++)
			if(q[i].op == 2)ans[q[i].id] = l;
		return;
	}
	int mid = (l + r) >> 1;
	bool fl = false, fr = false;
	int L = 0, R = 0;
	tr[1].rec = 1, tr[1].tag = tr[1].sum = 0;
	for(int i = st; i <= ed; i++)
	{
		if(q[i].op == 1)
		{
			if(q[i].v > mid)
			{
				segadd(1, q[i].l, q[i].r, 1, n, 1);
				qr[++R] = q[i];
			}
			else ql[++L] = q[i];
		}
		else
		{
			ll val = segsum(1, q[i].l, q[i].r, 1, n);
			if(val < q[i].v)
			{
				q[i].v -= val;
				fl = true;
				ql[++L] = q[i];
			}
			else
			{
				fr = true;
				qr[++R] = q[i];
			}
		}
	}
	for(int i = 1; i <= L; i++)q[st + i - 1] = ql[i];
	for(int i = L + 1; i <= L + R; i++)q[st + i - 1] = qr[i - L];
	if(fl)solve(st, st + L - 1, l, mid);
	if(fr)solve(st + L, ed, mid + 1, r);
}
int Q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int op, l, r, v;
		scanf("%d%d%d%d", &op, &l, &r, &v);
		q[i].op = op, q[i].l = l, q[i].r = r, q[i].v = v;
		if(op == 2)q[i].id = ++Q;
	}
	solve(1, m, -n, n);
	for(int i = 1; i <= Q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
