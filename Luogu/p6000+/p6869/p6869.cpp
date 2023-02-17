#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], id[M], idx;
void add(int a, int b,int c)
{
	e[idx] = b, ne[idx] = h[a], id[idx] = c, h[a] = idx++;
}
ll c[N], d[N], cnt[N];
int tag[N];
int fa[N], son[N], sz[N], dep[N], top[N];
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		tag[id[i]] = e[i];
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] >= sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	top[p] = t;
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
void dfs3(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs3(e[i], p);
		cnt[p] += cnt[e[i]];
	}
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d%lld%lld", &u, &v, &c[i], &d[i]);
		add(u, v, i), add(v, u, i);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i = 1; i < n; i++)
	{
		int g = lca(i, i + 1);
		cnt[i]++, cnt[i + 1]++, cnt[g] -= 2;
	}
	dfs3(1, 0);
	ll res = 0;
	for(int i = 1; i < n; i++)
	{
		ll tmp = c[i] * cnt[tag[i]];
		if(tmp > d[i])tmp = d[i];
		res += tmp;
	}
	printf("%lld\n", res);
	return 0;
}
