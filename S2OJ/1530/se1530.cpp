#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 100010;
int n, m, lim;
int a[N];
struct SegTree
{
	int l, r;
	int tag;
	int s;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].s = tr[p << 1].s | tr[p << 1 | 1].s;
}
void pushdown(int p)
{
	if(tr[p].tag == -1)return;
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	left.s = (1 << root.tag);
	rght.s = (1 << root.tag);
	left.tag = root.tag;
	rght.tag = root.tag;
	root.tag = -1;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].tag = -1;
	if(l == r)
	{
		tr[p].s = (1 << a[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segchg(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].tag = k;
		tr[p].s = (1 << k);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segchg(p << 1, l, r, k);
	if(r > mid)segchg(p << 1 | 1, l, r, k);
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].s;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res |= segsum(p << 1, l, r);
	if(r > mid)res |= segsum(p << 1 | 1, l, r);
	return res;
}
struct Query
{
	int op, l, r, x;
};
Query q[N];
int cntw;
unordered_map<int, int>dic;
int w[15];
bool able[1030][M];
int main()
{
	scanf("%d%d%d", &n, &lim, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(!dic.count(a[i]))
		{
			w[cntw] = a[i];
			dic.emplace(a[i], cntw++);
		}
		a[i] = dic[a[i]];
	}
	for(int i = 1; i <= m; i++)
	{
		int op, l, r, x;
		scanf("%d%d%d%d", &op, &l, &r, &x);
		if(op == 1 && !dic.count(x))
		{
			w[cntw] = x;
			dic.emplace(x, cntw++);
		}
		if(op == 1)x = dic[x];
		q[i] = { op,l,r,x };
	}
	build(1, 1, n);
	able[0][0] = true;
	for(int S = 1; S < (1 << cntw); S++)
	{
		for(int i = 0; i < cntw; i++)
		{
			if(!(S & (1 << i)))continue;
			int T = S ^ (1 << i);
			for(int k = 0; k <= lim; k++)
			{
				if(!able[T][k])continue;
				if(able[S][k])continue;
				for(int j = 0; k + j <= lim; j += w[i])
					able[S][k + j] = true;
			}
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int op = q[i].op, l = q[i].l, r = q[i].r, x = q[i].x;
		if(op == 1)
		{
			segchg(1, l, r, x);
		}
		else if(op == 2)
		{
			int S = segsum(1, l, r);
			if(able[S][x])puts("Yes");
			else puts("No");
		}
	}
	return 0;
}