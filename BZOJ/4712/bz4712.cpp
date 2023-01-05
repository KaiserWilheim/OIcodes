#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
const ll INF = 1e16;
struct Matrix
{
	ll a[2][2];
	void init()
	{
		a[0][0] = a[0][1] = a[1][0] = a[1][1] = INF;
	}
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res;
		res.init();
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				for(int k = 0; k < 2; k++)
					res.a[i][j] = min(res.a[i][j], lhs.a[i][k] + rhs.a[k][j]);
		return res;
	}
};
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll a[N];
int fa[N], dep[N], son[N], sz[N], top[N];
int dfn[N], id[N], tot;
int ntop[N];
ll f[N], g[N];
void dfs1(int p, int fa, int depth)
{
	::fa[p] = fa, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p, depth + 1);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	dfn[p] = ++tot, id[tot] = p, top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
}
void dfs3(int p, int fa)
{
	f[p] = g[p] = INF;
	if(!son[p])
	{
		f[p] = min(a[p], f[p] + g[p]);
		return;
	}
	dfs3(son[p], p);
	f[p] = f[son[p]], g[p] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || e[i] == son[p])continue;
		dfs3(e[i], p);
		g[p] += f[e[i]];
	}
	f[p] = min(a[p], f[p] + g[p]);
}
struct SegTree
{
	int l, r;
	Matrix sum;
};
SegTree tr[N << 3];
Matrix val[N];
void pushup(int p)
{
	tr[p].sum = tr[p << 1 | 1].sum * tr[p << 1].sum;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum.init();
		tr[p].sum = val[id[l]];
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
		tr[p].sum.init();
		tr[p].sum = val[id[pos]];
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segchg(p << 1, pos);
	else segchg(p << 1 | 1, pos);
	pushup(p);
}
Matrix segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(r <= mid)return segsum(p << 1, l, r);
	else if(l > mid)return segsum(p << 1 | 1, l, r);
	else return segsum(p << 1 | 1, l, r) * segsum(p << 1, l, r);
}
void chgpath(int p)
{
	while(p)
	{
		val[p].a[0][1] = a[p];
		val[p].a[1][1] = g[p];
		segchg(1, dfn[p]);
		if(p == 1)break;
		p = top[p];
		g[fa[p]] -= f[p];
		f[p] = segsum(1, dfn[p], dfn[ntop[top[p]]]).a[0][1];
		g[fa[p]] += f[p];
		p = fa[p];
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	dfs3(1, 0);
	for(int i = 1; i <= n; i++)
	{
		val[i].init();
		val[i].a[0][0] = 0;
		val[i].a[0][1] = a[i];
		val[i].a[1][1] = g[i];
	}
	build(1, 1, n);
	for(int i = 1; i <= n; i++)
	{
		if(top[i] != i)continue;
		int u = i;
		while(son[u])u = son[u];
		ntop[i] = u;
	}
	scanf("%d", &m);
	while(m--)
	{
		char op[5];
		scanf("%s", op);
		if(op[0] == 'Q')
		{
			int x;
			scanf("%d", &x);
			ll res = segsum(1, dfn[x], dfn[ntop[top[x]]]).a[0][1];
			printf("%lld\n", res);
		}
		else
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x] += y;
			chgpath(x);
		}
	}
	return 0;
}
