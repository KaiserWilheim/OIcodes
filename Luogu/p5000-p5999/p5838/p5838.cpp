#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int w[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], son[N], dep[N], sz[N], top[N];
int dfn[N], id[N], cnt;
vector<int>v[N];
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
bool solve(int p, int q, int c)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		auto k = lower_bound(v[c].begin(), v[c].end(), dfn[top[p]]);
		if(k != v[c].end() && *k <= dfn[p])return true;
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	auto k = lower_bound(v[c].begin(), v[c].end(), dfn[q]);
	if(k != v[c].end() && *k <= dfn[p])return true;
	return false;
}
char ans[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i = 1; i <= n; i++)
		v[w[id[i]]].push_back(i);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		ans[i] = '0' + solve(a, b, c);
	}
	printf("%s\n", ans + 1);
	return 0;
}
