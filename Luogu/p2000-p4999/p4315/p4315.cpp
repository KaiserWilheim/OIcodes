#include<bits/stdc++.h> 
using namespace std;
const int N = 100010, M = N << 1;
int cnt, h[N], ne[M], e[M], w[M], fr[M];
int n, a[N], t[N << 2], tag[N << 2], cov[N << 2];
int sz[N], son[N], dfn[N], Index, top[N], rk[N], dep[N], fa[N];
string s;
void AddEdge(int u, int v, int c)
{
	e[++cnt] = v;
	ne[cnt] = h[u];
	h[u] = cnt;
	w[cnt] = c;
	fr[cnt] = u;
}
void dfs1(int u)
{
	sz[u] = 1;
	son[u] = 0;
	for(int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if(v == fa[u]) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		rk[v] = w[i];
		dfs1(v);
		sz[u] += sz[v];
		if(sz[son[u]] < sz[v]) son[u] = v;
	}
}
void dfs2(int u, int rt)
{
	dfn[u] = ++Index;
	top[u] = rt;
	a[Index] = rk[u];
	if(son[u]) dfs2(son[u], rt);
	for(int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
void PushUp(int rt)
{
	t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}
void PushDown(int rt)
{
	if(~cov[rt])
	{
		cov[rt << 1] = cov[rt << 1 | 1] = cov[rt];
		t[rt << 1] = t[rt << 1 | 1] = cov[rt];
		tag[rt << 1] = tag[rt << 1 | 1] = 0;
		cov[rt] = -1;
	}
	tag[rt << 1] += tag[rt];
	tag[rt << 1 | 1] += tag[rt];
	t[rt << 1] += tag[rt];
	t[rt << 1 | 1] += tag[rt];
	tag[rt] = 0;
}
void Build(int rt, int l, int r)
{
	cov[rt] = -1;
	if(l == r)
	{
		t[rt] = a[l];
		return;
	}
	int mid = l + r >> 1;
	Build(rt << 1, l, mid);
	Build(rt << 1 | 1, mid + 1, r);
	PushUp(rt);
}
void ModifyCover(int rt, int l, int r, int tl, int tr, int val)
{
	if(tl <= l && r <= tr)
	{
		t[rt] = cov[rt] = val;
		tag[rt] = 0;
		return;
	}
	PushDown(rt);
	int mid = l + r >> 1;
	if(tl <= mid) ModifyCover(rt << 1, l, mid, tl, tr, val);
	if(tr > mid) ModifyCover(rt << 1 | 1, mid + 1, r, tl, tr, val);
	PushUp(rt);
}
void ModifyAdd(int rt, int l, int r, int tl, int tr, int val)
{
	if(tl <= l && r <= tr)
	{
		t[rt] += val;
		tag[rt] += val;
		return;
	}
	PushDown(rt);
	int mid = l + r >> 1;
	if(tl <= mid) ModifyAdd(rt << 1, l, mid, tl, tr, val);
	if(tr > mid) ModifyAdd(rt << 1 | 1, mid + 1, r, tl, tr, val);
	PushUp(rt);
}
int Query(int rt, int l, int r, int tl, int tr)
{
	if(tl <= l && r <= tr) return t[rt];
	PushDown(rt);
	int mid = l + r >> 1, res = 0;
	if(tl <= mid) res = max(res, Query(rt << 1, l, mid, tl, tr));
	if(tr > mid) res = max(res, Query(rt << 1 | 1, mid + 1, r, tl, tr));
	return res;
}
void ModifyCoverOnTree(int u, int v, int val)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ModifyCover(1, 1, n, dfn[top[u]], dfn[u], val);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	ModifyCover(1, 1, n, dfn[u] + 1, dfn[v], val);
}
void ModifyAddOnTree(int u, int v, int val)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ModifyAdd(1, 1, n, dfn[top[u]], dfn[u], val);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	ModifyAdd(1, 1, n, dfn[u] + 1, dfn[v], val);
}
int QueryMaxnOnTree(int u, int v)
{
	int res = 0;
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		res = max(res, Query(1, 1, n, dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	res = max(res, Query(1, 1, n, dfn[u] + 1, dfn[v]));
	return res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		AddEdge(x, y, z);
		AddEdge(y, x, z);
	}
	dfs1(1);
	dfs2(1, 1);
	Build(1, 1, n);
	while(1)
	{
		int x, y, z;
		cin >> s;
		if(s == "Stop") break;
		else
		{
			scanf("%d %d", &x, &y);
			if(s == "Change")
			{
				x <<= 1;
				int u = fr[x], v = e[x];
				if(dep[u] > dep[v]) swap(u, v);
				ModifyCoverOnTree(u, v, y);
			}
			else if(s == "Cover")
			{
				scanf("%d", &z);
				ModifyCoverOnTree(x, y, z);
			}
			else if(s == "Add")
			{
				scanf("%d", &z);
				ModifyAddOnTree(x, y, z);
			}
			else if(s == "Max") printf("%d\n", QueryMaxnOnTree(x, y));
		}
	}
	return 0;
}

