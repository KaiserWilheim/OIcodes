#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 200010;
const ll INF = 1e15;
struct Matrix
{
	ll m[2][2];
	Matrix() { memset(m, -0x3f, sizeof(m)); }
	inline Matrix operator * (Matrix b)
	{
		Matrix c;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					c.m[i][j] = max(c.m[i][j], m[i][k] + b.m[k][j]);
		return c;
	}
};

int n, m;
ll a[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
}
int fa[N], son[N], sz[N], dep[N], top[N];
int id[N], dfn[N], ed[N], cnt;
ll f[N][2];
Matrix val[N];

struct SegTree
{
	int l, r;
	Matrix v;
}tr[N << 3];
void pushup(int p)
{
	tr[p].v = tr[p << 1].v * tr[p << 1 | 1].v;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if (l == r)
	{
		tr[p].v = val[dfn[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int x)
{
	if (tr[p].l == tr[p].r)
	{
		tr[p].v = val[dfn[x]];
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if (x <= mid)segadd(p << 1, x);
	else segadd(p << 1 | 1, x);
	pushup(p);
}
Matrix segsum(int p, int l, int r)
{
	if (tr[p].l == l && tr[p].r == r)return tr[p].v;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if (r <= mid)
		return segsum(p << 1, l, r);
	else if (l > mid)
		return segsum(p << 1 | 1, l, r);
	else
		return segsum(p << 1, l, mid) * segsum(p << 1 | 1, mid + 1, r);
}

void dfs1(int p, int father)
{
	fa[p] = father, dep[p] = dep[father] + 1, sz[p] = 1;
	for (int i = h[p]; i; i = ne[i])
	{
		int j = e[i];
		if (j == father)continue;
		dfs1(j, p);
		sz[p] += sz[j];
		if (sz[j] > sz[son[p]])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, dfn[cnt] = p, top[p] = t;
	ed[t] = max(ed[t], cnt);
	f[p][0] = 0, f[p][1] = a[p];
	val[p].m[0][0] = val[p].m[0][1] = 0;
	val[p].m[1][0] = a[p];
	if (son[p])
	{
		dfs2(son[p], t);
		f[p][0] += max(f[son[p]][0], f[son[p]][1]);
		f[p][1] += f[son[p]][0];
	}
	for (int i = h[p]; i; i = ne[i])
	{
		int j = e[i];
		if (j == fa[p] || j == son[p])continue;
		dfs2(j, j);
		f[p][0] += max(f[j][0], f[j][1]);
		f[p][1] += f[j][0];
		val[p].m[0][0] += max(f[j][0], f[j][1]);
		val[p].m[0][1] = val[p].m[0][0];
		val[p].m[1][0] += f[j][0];
	}
}
void addpath(int p, ll k)
{
	val[p].m[1][0] += k - a[p];
	a[p] = k;
	Matrix bef, aft;
	while (p)
	{
		bef = segsum(1, id[top[p]], ed[top[p]]);
		segadd(1, id[p]);
		aft = segsum(1, id[top[p]], ed[top[p]]);
		p = fa[top[p]];
		val[p].m[0][0] += max(aft.m[0][0], aft.m[1][0]) - max(bef.m[0][0], bef.m[1][0]);
		val[p].m[0][1] = val[p].m[0][0];
		val[p].m[1][0] += aft.m[0][0] - bef.m[0][0];
	}
}
char type[10];
ll sum;
int main()
{
	scanf("%d%d", &n, &m);
	cin >> type;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int u, x, v, y;
		scanf("%d%d%d%d", &u, &x, &v, &y);
		if ((x == 0 && y == 0) && (fa[u] == v || fa[v] == u))
		{
			puts("-1");
			continue;
		}
		ll v1 = a[u], v2 = a[v];
		addpath(u, a[u] + (x == 1 ? -INF : INF));
		addpath(v, a[v] + (y == 1 ? -INF : INF));
		Matrix ans = segsum(1, id[1], ed[1]);
		ll res = sum - max(ans.m[0][0], ans.m[1][0]) + (x == 1 ? 0 : INF) + (y == 1 ? 0 : INF);
		printf("%lld\n", res);
		addpath(u, v1);
		addpath(v, v2);
	}
	return 0;
}
