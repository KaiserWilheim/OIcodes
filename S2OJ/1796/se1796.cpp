#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 2;
int n, m, q;
vector<pair<int, int>>edge;
int hs[N], h[N], e[M], ne[M], idx;
void add(int a, int b, int *h)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
int dcc[N], dc;
void tarjan(int p, int from)
{
	dfn[p] = low[p] = ++cnt;
	sta[++tt] = p;
	for(int i = hs[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j, i);
			low[p] = min(low[p], low[j]);
		}
		else if(i != (from ^ 1))
		{
			low[p] = min(low[p], dfn[j]);
		}
	}
	if(dfn[p] == low[p])
	{
		dc++;
		while(sta[tt] != p)
		{
			dcc[sta[tt]] = dc;
			tt--;
		}
		dcc[sta[tt]] = dc;
		tt--;
	}
}
int rt1, rt2;
int fa[N], dep[N], son[N], mdep[N];
int nw[N], tot;
void dfs1(int p, int father, int depth)
{
	dep[p] = depth;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs1(e[i], p, depth + 1);
	}
}
void dfs2(int p, int father)
{
	fa[p] = father, dep[p] = dep[father] + 1;
	mdep[p] = dep[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs2(e[i], p);
		if(mdep[e[i]] > mdep[son[p]])
		{
			mdep[p] = mdep[e[i]];
			son[p] = e[i];
		}
	}
}
void dfs3(int p, int t)
{
	if(p == t)
	{
		if(p != rt1)nw[++tot] = mdep[p] - dep[fa[p]];
		else nw[++tot] = mdep[p] - dep[p];
	}
	if(!son[p])return;
	dfs3(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs3(e[i], e[i]);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	memset(hs, -1, sizeof(hs));
	scanf("%d%d", &n, &m);
	scanf("%d", &q);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b, hs), add(b, a, hs);
		edge.emplace_back(a, b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i, -1);
	for(int i = 0; i < m; i++)
	{
		int u = dcc[edge[i].first], v = dcc[edge[i].second];
		if(u == v)continue;
		add(u, v, h), add(v, u, h);
	}
	dfs1(1, 0, 1);
	for(int i = 1; i <= n; i++)
		if(dep[i] > dep[rt1])rt1 = i;
	dfs1(rt1, 0, 1);
	for(int i = 1; i <= n; i++)
		if(dep[i] > dep[rt2])rt2 = i;
	dfs2(rt1, 0);
	dfs3(rt1, rt1);
	sort(nw + 1, nw + 1 + cnt, greater<int>());
	int ans = nw[1];
	printf("%d\n", ans);
	for(int i = 2; i <= q; i++)
	{
		if((i - 1) * 2 <= tot)ans += nw[(i - 1) * 2];
		if((i - 1) * 2 + 1 <= tot)ans += nw[(i - 1) * 2 + 1];
		printf("%d\n", ans);
	}
	return 0;
}