#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], w[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct segtree
{
	int l, r;
	ll max, sum;
}tr[N << 3];
void add(int a, int b)
{
	e[idx] = b;
	ne[idx] = h[a];
	h[a] = idx++;
	return;
}
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father) continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j]) son[p] = j;
	}
	return;
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = w[p], top[p] = t;
	if(!son[p]) return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
	return;
}
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
	return;
}
void build(int p, int l, int r)
{
	if(l == r)
	{
		tr[p] = { l, r, nw[r],nw[r] };
		return;
	}
	tr[p].l = l, tr[p].r = r;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}
void change(int p, int ed, int k)
{
	if((tr[p].l == ed) && (tr[p].r == ed))
	{
		tr[p].max = k;
		tr[p].sum = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(ed <= mid)change(p << 1, ed, k);
	if(ed > mid)change(p << 1 | 1, ed, k);
	pushup(p);
	return;
}
ll segsum(int p, int l, int r)
{
	if((l <= tr[p].l) && (r >= tr[p].r)) return tr[p].sum;
	//pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = 0;
	if(l <= mid) res += segsum(p << 1, l, r);
	if(r > mid) res += segsum(p << 1 | 1, l, r);
	return res;
}
ll segmax(int p, int l, int r)
{
	if((l <= tr[p].l) && (r >= tr[p].r)) return tr[p].max;
	//pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	ll res = -114514;
	if(l <= mid) res = max(res, segmax(p << 1, l, r));
	if(r > mid) res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
ll sumpath(int p, int q)
{
	ll res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]]) swap(p, q);
		res += segsum(1, id[top[p]], id[p]);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q]) swap(p, q);
	res += segsum(1, id[q], id[p]);
	return res;
}
ll maxpath(int p, int q)
{
	ll res = -114514;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]]) swap(p, q);
		res = max(res, segmax(1, id[top[p]], id[p]));
		p = fa[top[p]];
	}
	if(dep[p] < dep[q]) swap(p, q);
	res = max(res, segmax(1, id[q], id[p]));
	return res;
}
int main()
{
	scanf("%d", &n);
	memset(h, -1, sizeof h);
	for(int i = 2; i <= n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	for(int i = 1; i <= n; i++)scanf("%d", &w[i]);
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	scanf("%d", &m);
	while(m--)
	{
		string op;
		int x, y;
		cin >> op;
		scanf("%d%d", &x, &y);
		if(op[1] == 'H')
		{
			change(1, id[x], y);
		}
		else if(op[1] == 'M')
		{
			printf("%lld\n", maxpath(x, y));
		}
		else if(op[1] == 'S')
		{
			printf("%lld\n", sumpath(x, y));
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
