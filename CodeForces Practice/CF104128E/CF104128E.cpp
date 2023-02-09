#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010, M = N << 1;
int n;
int lg2[N];
int a[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
struct STable
{
	int f[N][20];
	void build(int *a)
	{
		for(int i = 0; i < n; i++)memset(f[i], 63, sizeof(f[i]));
		for(int i = 0; i < n; i++)f[i][0] = a[i];
		for(int j = 1; j <= 18; j++)
			for(int i = 0; i + (1 << j) - 1 < n; i++)
				f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
	}
	int query(int l, int r)
	{
		int k = lg2[r - l + 1];
		return min(f[l][k], f[r - (1 << k) + 1][k]);
	}
}ST;
int fa[N], son[N], dep[N], sz[N], top[N];
int dfn[N], cnt;
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1, son[p] = 0;
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
	top[p] = t, dfn[p] = ++cnt;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
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
int tmp[N], sta[N], tt, lim;
vector<int>v[N], pos[N];
ll f[N];
void work(int x, int d)
{
	if(v[x].empty())
	{
		f[x] = ST.query(0, d - 1);
		return;
	}
	ll t = 0;
	for(auto i : v[x])work(i, d), t += f[i];
	f[x] = min(t, 1ll * ST.query(d - dep[x], d - 1));
	v[x].clear();
}
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
ll calc(int d)
{
	lim = 0;
	for(auto i : pos[d])tmp[++lim] = i;
	sort(tmp + 1, tmp + 1 + lim, cmp);
	sta[tt = 0] = 1;
	for(int i = 1; i <= lim; i++)
	{
		int x = tmp[i];
		if(x == 1)continue;
		if(!tt)
		{
			sta[++tt] = x;
			continue;
		}
		int g = lca(x, sta[tt]);
		while(tt && dfn[g] <= dfn[sta[tt - 1]])v[sta[tt - 1]].push_back(sta[tt]), tt--;
		if(sta[tt] != g)v[g].push_back(sta[tt]), sta[tt] = g;
		sta[++tt] = x;
	}
	while(tt)v[sta[tt - 1]].push_back(sta[tt]), tt--;
	work(1, d);
	return f[1];
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		h[i] = -1, pos[i].clear();
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	ST.build(a);
	for(int i = 1; i <= n; i++)pos[dep[i]].push_back(i);
	ll ans = a[0];
	for(int i = 2; i <= n; i++)if(!pos[i].empty())ans += calc(i);
	printf("%lld\n", ans);
}
int main()
{
	for(int i = 2; i <= 100010; i++)lg2[i] = lg2[i / 2] + 1;
	int T;
	scanf("%d", &T);
	while(T--)
	{
		cnt = idx = 0;
		solve();
	}
	return 0;
}
