#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m, rt, mod;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct segtree
{
	int l, r;
}tr[N << 3];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
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
}
void build(int p, int l, int r)
{
	tr[p] = { l, r };
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
int lca(int u, int v)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] > dep[top[v]])
			u = fa[top[u]];
		else
			v = fa[top[v]];
	}
	return dep[u] > dep[v] ? v : u;
}
int main()
{
	scanf("%d%d%d", &n, &m, &rt);
	memset(h, -1, sizeof h);
	for(int i = 0; i < n - 1; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs1(rt, 0, 1);
	dfs2(rt, rt);
	build(1, 1, n);
	while(m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x, y));
	}

	return 0;
}
