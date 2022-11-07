#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n;
int h[N], e[M], ne[M], id[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, id[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], son[N], dep[N], sz[N];
int l[N], r[N], nw[N], dfn;
int f[N];
void dfs1(int p, int father)
{
	fa[p] = father, sz[p] = 1;
	l[p] = ++dfn, nw[dfn] = p;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs1(e[i], p);
		f[e[i]] = id[i];
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
	r[p] = dfn;
}
int col[N];
int tot[N], cnt[N];
ll ans[N], pre;
void add(int i)
{
	pre -= 1ll * cnt[i] * (tot[i] - cnt[i]);
	cnt[i]++;
	pre += 1ll * cnt[i] * (tot[i] - cnt[i]);
}
void del(int i)
{
	pre -= 1ll * cnt[i] * (tot[i] - cnt[i]);
	cnt[i]--;
	pre += 1ll * cnt[i] * (tot[i] - cnt[i]);
}
void dfs2(int p, bool keep)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], false);
	}
	if(son[p])dfs2(son[p], true);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		for(int j = l[e[i]]; j <= r[e[i]]; j++)
			add(col[nw[j]]);
	}
	add(col[p]);
	ans[f[p]] = pre;
	if(!keep)
	{
		for(int i = l[p]; i <= r[p]; i++)
			del(col[nw[i]]);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		tot[col[i]]++;
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v, i), add(v, u, i);
	}
	dfs1(1, 0);
	dfs2(1, true);
	for(int i = 1; i < n; i++)
		printf("%lld ", ans[i]);
	return 0;
}
