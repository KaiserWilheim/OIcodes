#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = 6000010;
int n, m, R;
int x[N], y[N], z[N];
int rt[N], ans[N];
//全局变量
struct SegTree
{
	int ls, rs;
	int d, t;
}tr[M];
int cnt;
void pushup(int p)
{
	if(tr[tr[p].ls].d >= tr[tr[p].rs].d)
	{
		tr[p].d = tr[tr[p].ls].d;
		tr[p].t = tr[tr[p].ls].t;
	}
	else
	{
		tr[p].d = tr[tr[p].rs].d;
		tr[p].t = tr[tr[p].rs].t;
	}
}
int segchg(int p, int l, int r, int pos, int k)
{
	if(!p)p = ++cnt;
	if(l == r)
	{
		tr[p].d += k;
		tr[p].t = l;
		return p;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)tr[p].ls = segchg(tr[p].ls, l, mid, pos, k);
	if(pos > mid)tr[p].rs = segchg(tr[p].rs, mid + 1, r, pos, k);
	pushup(p);
	return p;
}
int segmer(int p, int q, int l, int r)
{
	if(!p)return q;
	if(!q)return p;
	if(l == r)
	{
		tr[p].d += tr[q].d;
		tr[p].t = l;
		return p;
	}
	int mid = (l + r) >> 1;
	tr[p].ls = segmer(tr[p].ls, tr[q].ls, l, mid);
	tr[p].rs = segmer(tr[p].rs, tr[q].rs, mid + 1, r);
	pushup(p);
	return p;
}
//线段树
int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
//链式前向星
int top[N], fa[N], dep[N], son[N], sz[N];
void dfs1(int p, int father, int depth)
{
	fa[p] = father, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[j] > sz[son[p]])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p])continue;
		dfs2(j, j);
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
//树剖LCA
void redfs(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(dep[j] > dep[p])
		{
			redfs(j);
			rt[p] = segmer(rt[p], rt[j], 1, R);
		}
	}
	if(tr[rt[p]].d)ans[p] = tr[rt[p]].t;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		R = max(R, z[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int u = lca(x[i], y[i]);
		rt[x[i]] = segchg(rt[x[i]], 1, R, z[i], 1);
		rt[y[i]] = segchg(rt[y[i]], 1, R, z[i], 1);
		rt[u] = segchg(rt[u], 1, R, z[i], -1);
		if(fa[u])rt[fa[u]] = segchg(rt[fa[u]], 1, R, z[i], -1);
	}
	redfs(1);
	for(int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}
