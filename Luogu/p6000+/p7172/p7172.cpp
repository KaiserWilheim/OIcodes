#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010, M = N << 1;
int n, m, q;
int a[N];
int siz[N], id[M];
struct SegTree
{
	int ls, rs;
	int sum;
	int id;
};
SegTree tr[N * 40];
int rt[N], idx;
void pushup(int p)
{
	tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum;
}
void build(int &p, int l, int r)
{
	p = ++idx;
	if(l == r)
	{
		tr[p].id = ++m;
		tr[p].sum = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(tr[p].ls, l, mid);
	build(tr[p].rs, mid + 1, r);
	pushup(p);
}
void segmod(int &p, int q, int l, int r, int k)
{
	p = ++idx;
	tr[p] = tr[q], tr[p].id = 0;
	if(l == r)
	{
		tr[p].sum = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if(k <= tr[tr[p].ls].sum)segmod(tr[p].ls, tr[q].ls, l, mid, k);
	else segmod(tr[p].rs, tr[q].rs, mid + 1, r, k - tr[tr[p].ls].sum);
	pushup(p);
}
void segchg(int &p, int q, int l, int r, int k, int w)
{
	p = ++idx;
	tr[p] = tr[q];
	if(l == r)
	{
		tr[p].id = w;
		return;
	}
	int mid = (l + r) >> 1;
	if(k <= tr[tr[p].ls].sum)segchg(tr[p].ls, tr[q].ls, l, mid, k, w);
	else segchg(tr[p].rs, tr[q].rs, mid + 1, r, k - tr[tr[p].ls].sum, w);
	pushup(p);
}
int query(int p, int l, int r, int k)
{
	if(l == r)return tr[p].id;
	int mid = (l + r) >> 1;
	if(k <= tr[tr[p].ls].sum)return query(tr[p].ls, l, mid, k);
	return query(tr[p].rs, mid + 1, r, k - tr[tr[p].ls].sum);
}
vector<int>e[M];
int fa[M], dep[M], son[M], sz[M], top[M];
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i : e[p])
	{
		if(i == fa)continue;
		dfs1(i, p);
		sz[p] += sz[i];
		if(sz[i] > sz[son[p]])son[p] = i;
	}
}
void dfs2(int p, int t)
{
	top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i : e[p])
	{
		if(i == fa[p] || i == son[p])continue;
		dfs2(i, i);
	}
}
int lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
signed main()
{
	scanf("%lld%lld", &n, &q);
	int t;
	scanf("%lld", &t);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		siz[i] = i * (i + 1) / 2;
	for(int i = 1; i <= n + 1; i++)
		id[i] = n * (n + 1) / 2 + i;
	build(rt[n + 1], 1, n + 1);
	for(int i = n; i; i--)
	{
		int p = a[i] - siz[i - 1];
		id[++m] = a[i];
		rt[i] = rt[i + 1];
		segmod(rt[i], rt[i], 1, n + 1, p + 1);
		segchg(rt[i], rt[i], 1, n + 1, p, m);
		int u = query(rt[i + 1], 1, n + 1, p);
		int v = query(rt[i + 1], 1, n + 1, p + 1);
		e[m].push_back(u), e[m].push_back(v);
	}
	dfs1(m, 0);
	dfs2(m, m);
	int lans = 0, mod = (n + 1) * (n + 2) / 2;
	while(q--)
	{
		int u, v;
		scanf("%lld%lld", &u, &v);
		u = (u - 1 + lans * t) % mod + 1;
		v = (v - 1 + lans * t) % mod + 1;
		int du = lower_bound(siz, siz + 1 + n, u) - siz,
			dv = lower_bound(siz, siz + 1 + n, v) - siz;
		int pu = query(rt[du], 1, n + 1, u - siz[du - 1]),
			pv = query(rt[dv], 1, n + 1, v - siz[dv - 1]);
		lans = id[lca(pu, pv)];
		lans = min(min(u, v), lans);
		printf("%lld\n", lans);
	}
	return 0;
}
