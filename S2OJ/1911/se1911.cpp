#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int h[N], e[M], ne[M], idx;
int deg[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], son[N], dep[N], sz[N], top[N];
int dfn[N], id[N], cnt;
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	top[p] = t, dfn[p] = ++cnt, id[cnt] = p;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
}
struct SegTree
{
	int l, r;
	int maxn;
	int tag;
};
SegTree tr[N << 3];
void pushup(int p)
{
	tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
}
void pushdown(int p)
{
	if(!tr[p].tag)return;
	tr[p << 1].maxn += tr[p].tag;
	tr[p << 1 | 1].maxn += tr[p].tag;
	tr[p << 1].tag += tr[p].tag;
	tr[p << 1 | 1].tag += tr[p].tag;
	tr[p].tag = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].maxn = 0;
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void segadd(int p, int l, int r, int k)
{
	if(l <= tr[p].l && tr[p].r <= r)
	{
		tr[p].tag += k;
		tr[p].maxn += k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
int __lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
void addtree(int p)
{
	segadd(1, dfn[p], dfn[p] + sz[p] - 1, 1);
}
int main()
{
	memset(h, -1, sizeof(h));
	n = read(), m = read();
	for(int i = 1; i < n; i++)
	{
		int u, v;
		u = read(), v = read();
		add(u, v), add(v, u);
		deg[u]++, deg[v]++;
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	int tot = 0;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		u = read(), v = read();
		if(u == v)tot++;
		else
		{
			if(dep[u] > dep[v])swap(u, v);
			if(__lca(u, v) == u)
			{
				addtree(v);
				for(int i = h[u]; ~i; i = ne[i])
				{
					if(e[i] == fa[u] || __lca(e[i], v) == e[i])continue;
					addtree(e[i]);
				}
				segadd(1, 1, dfn[u], 1);
				segadd(1, dfn[u] + sz[u], n, 1);
			}
			else
			{
				addtree(u), addtree(v);
			}
		}
		printf("%d\n", tot + tr[1].maxn);
	}
	return 0;
}
