#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 500010;
int n, m, q;
int a[N], tmp[N];
struct DSU
{
	int p[M];
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
			p[i] = i;
	}
	int find(int x)
	{
		if(p[x] != x)p[x] = find(p[x]);
		return p[x];
	}
};
DSU dsu;
struct SegTree
{
	int ls, rs;
	int sum;
};
SegTree tr[N * 20];
int rt[N], cnt;
int segadd(int q, int l, int r, int pos)
{
	int p = ++cnt;
	tr[p].sum = tr[q].sum + 1;
	if(l == r)return p;
	int mid = (l + r) >> 1;
	if(pos <= mid)
	{
		tr[p].rs = tr[q].rs;
		tr[p].ls = segadd(tr[q].ls, l, mid, pos);
	}
	else
	{
		tr[p].ls = tr[q].ls;
		tr[p].rs = segadd(tr[q].rs, mid + 1, r, pos);
	}
	return p;
}
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &rhs)const
	{
		return w < rhs.w;
	}
};
Edge edge[M];
int h[N], e[N], ne[N], idx;
int val[N];
int ls[N], rs[N];
int fa[N][20];
int tot, dfn;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int query(int p, int x, int k)
{
	int l = 1, r = tot;
	for(int j = 18; ~j; j--)
		if(fa[p][j] && val[fa[p][j]] <= x)p = fa[p][j];
	int v = rt[rs[p]], u = rt[ls[p] - 1];
	if(tr[v].sum - tr[u].sum < k)return -1;
	while(l < r)
	{
		int tmp = tr[tr[v].rs].sum - tr[tr[u].rs].sum;
		int mid = (l + r) >> 1;
		if(tmp >= k)v = tr[v].rs, u = tr[u].rs, l = mid + 1;
		else v = tr[v].ls, u = tr[u].ls, r = mid, k -= tmp;
	}
	return tmp[r];
}
void dfs(int p)
{
	for(int i = 1; i <= 18; i++)
		fa[p][i] = fa[fa[p][i - 1]][i - 1];
	ls[p] = ++dfn;
	if(p <= n)rt[dfn] = segadd(rt[dfn - 1], 1, tot, a[p]);
	else rt[dfn] = rt[dfn - 1];
	for(int i = h[p]; ~i; i = ne[i])
		dfs(e[i]);
	rs[p] = dfn;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &q);
	dsu.init(n * 2);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = { u,v,w };
	}
	sort(edge + 1, edge + 1 + m);
	sort(tmp + 1, tmp + 1 + n);
	int len = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(tmp + 1, tmp + 1 + len, a[i]) - tmp;
	tot = n;
	for(int i = 1; i <= m; i++)
	{
		int u = dsu.find(edge[i].u), v = dsu.find(edge[i].v);
		if(u == v)continue;
		val[++tot] = edge[i].w, dsu.p[u] = dsu.p[v] = tot;
		add(tot, u), add(tot, v);
		fa[u][0] = fa[v][0] = tot;
		if(tot == n * 2 - 1)break;
	}
	for(int i = 1; i <= tot; i++)
		if(!ls[i])dfs(dsu.find(i));
	while(q--)
	{
		int v, x, k;
		scanf("%d%d%d", &v, &x, &k);
		printf("%d\n", query(v, x, k));
	}
	return 0;
}
