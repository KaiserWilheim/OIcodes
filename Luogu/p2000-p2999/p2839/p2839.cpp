#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20010;
int n, m;
int a[N];
struct SegTree
{
	int ls, rs;
	int sum, prf, suf;
	bool cl, cr;
};
SegTree tr[N * 40];
int rt[N], idx;
void pushup(int p)
{
	tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum;
	tr[p].prf = max(tr[tr[p].ls].prf, tr[tr[p].ls].sum + tr[tr[p].rs].prf);
	tr[p].suf = max(tr[tr[p].rs].suf, tr[tr[p].rs].sum + tr[tr[p].ls].suf);
}
int build(int l, int r)
{
	int p = ++idx;
	if(l == r)
	{
		if(a[l] <= 1)tr[p].sum = tr[p].prf = tr[p].suf = -1;
		else tr[p].sum = tr[p].prf = tr[p].suf = 1;
		return p;
	}
	int mid = (l + r) >> 1;
	tr[p].cl = tr[p].cr = true;
	tr[p].ls = build(l, mid);
	tr[p].rs = build(mid + 1, r);
	pushup(p);
	return p;
}
int segchg(int p, int q, int l, int r, int pos, int k, bool c)
{
	if(!c)p = ++idx;
	if(l == r)
	{
		tr[p].sum = tr[p].prf = tr[p].suf = k;
		return p;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)
	{
		if(!tr[p].cr)tr[p].rs = tr[q].rs;
		if(!tr[p].cl)
		{
			tr[p].cl = true;
			tr[p].ls = segchg(p, tr[q].ls, l, mid, pos, k, false);
		}
		else
		{
			tr[p].ls = segchg(tr[p].ls, tr[q].ls, l, mid, pos, k, true);
		}
	}
	else
	{
		if(!tr[p].cl)tr[p].ls = tr[q].ls;
		if(!tr[p].cr)
		{
			tr[p].cr = true;
			tr[p].rs = segchg(p, tr[q].rs, mid + 1, r, pos, k, false);
		}
		else
		{
			tr[p].rs = segchg(tr[p].rs, tr[q].rs, mid + 1, r, pos, k, true);
		}
	}
	pushup(p);
	return p;
}
int segsum(int p, int l, int r, int dl, int dr)
{
	if(l >= dl && r <= dr)return tr[p].sum;
	int mid = (l + r) >> 1;
	int res = 0;
	if(dl <= mid)res += segsum(tr[p].ls, l, mid, dl, dr);
	if(dr > mid)res += segsum(tr[p].rs, mid + 1, r, dl, dr);
	return res;
}
SegTree segprf(int p, int l, int r, int dl, int dr)
{
	if(l >= dl && r <= dr)return tr[p];
	int mid = (l + r) >> 1;
	if(dl <= mid && mid < dr)
	{
		SegTree res;
		SegTree left = segprf(tr[p].ls, l, mid, dl, dr);
		SegTree rght = segprf(tr[p].rs, mid + 1, r, dl, dr);
		res.sum = left.sum + rght.sum;
		res.prf = max(left.prf, left.sum + rght.prf);
		return res;
	}
	else if(dl <= mid)return segprf(tr[p].ls, l, mid, dl, dr);
	else return segprf(tr[p].rs, mid + 1, r, dl, dr);
}
SegTree segsuf(int p, int l, int r, int dl, int dr)
{
	if(l >= dl && r <= dr)return tr[p];
	int mid = (l + r) >> 1;
	if(dl <= mid && mid < dr)
	{
		SegTree res;
		SegTree left = segsuf(tr[p].ls, l, mid, dl, dr);
		SegTree rght = segsuf(tr[p].rs, mid + 1, r, dl, dr);
		res.sum = left.sum + rght.sum;
		res.suf = max(rght.suf, rght.sum + left.suf);
		return res;
	}
	else if(dl <= mid)return segsuf(tr[p].ls, l, mid, dl, dr);
	else return segsuf(tr[p].rs, mid + 1, r, dl, dr);
}
int q[5];
bool chq(int v)
{
	int sz = 0;
	if(q[1] + 1 <= q[2] - 1)sz = segsum(rt[v], 1, n, q[1] + 1, q[2] - 1);
	int suf = segprf(rt[v], 1, n, q[2], q[3]).prf;
	int prf = segsuf(rt[v], 1, n, q[0], q[1]).suf;
	return (prf + sz + suf) >= 0;
}
vector<int>pos[N];
int tmp[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	sort(tmp + 1, tmp + 1 + n);
	int len = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
	for(int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(tmp + 1, tmp + 1 + len, a[i]) - tmp;
		pos[a[i]].push_back(i);
	}
	rt[1] = build(1, n);
	for(int i = 2; i <= len; i++)
		for(int j = 0; j < pos[i - 1].size(); j++)
			rt[i] = segchg(rt[i], rt[i - 1], 1, n, pos[i - 1][j], -1, rt[i] > 0);
	scanf("%d", &m);
	int lans = 0;
	while(m--)
	{
		scanf("%d%d%d%d", &q[0], &q[1], &q[2], &q[3]);
		for(int i = 0; i < 4; i++)q[i] = (q[i] + lans) % n;
		sort(q, q + 4);
		for(int i = 0; i < 4; i++)q[i]++;
		int l = 1, r = len;
		int ans = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(chq(mid))ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		lans = tmp[ans];
		printf("%d\n", lans);
	}
	return 0;
}
