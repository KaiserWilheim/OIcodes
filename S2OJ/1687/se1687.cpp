#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 500010;
const ll mod = 998244353;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
vector<int>v[N];
int col[N];
int fa[N], dep[N], son[N], sz[N];
int dfn[N], top[N], cnt;
void dfs1(int p, int father, int depth)
{
	fa[p] = father, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs1(e[i], p, depth + 1);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	dfn[p] = ++cnt, top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
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
int val[N];
vector<int>ans;
void getans(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p])continue;
		getans(e[i]);
		val[p] += val[e[i]];
	}
	if(val[p] == 1)ans.push_back(col[p]);
}
bool cmpd(int x, int y)
{
	return dfn[x] < dfn[y];
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		v[col[i]].push_back(i);
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for(int i = 1; i <= m; i++)
	{
		if(v[i].empty())continue;
		sort(v[i].begin(), v[i].end(), cmpd);
		int lca = v[i][0];
		val[lca]++;
		for(int j = 1; j < v[i].size(); j++)
		{
			val[v[i][j]]++;
			val[__lca(v[i][j], v[i][j - 1])]--;
			lca = __lca(lca, v[i][j]);
		}
		val[fa[lca]]--;
	}
	getans(1);
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d ", i);
	putchar('\n');
	return 0;
}