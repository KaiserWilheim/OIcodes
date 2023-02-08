#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010, M = N << 1;
int n, k;
int h[N], e[M], ne[M], idx;
vector<int>G[M];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int col[N], cnt[M];
vector<int>v[N];
int sz[N], minn, rt, tot;
bool vis[M], tag[M];
void getrt(int p, int fa)
{
	sz[p] = 1;
	int maxn = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		getrt(e[i], p);
		sz[p] += sz[e[i]];
		maxn = max(maxn, sz[e[i]]);
	}
	maxn = max(maxn, tot - sz[p]);
	if(!rt || maxn < minn)minn = maxn, rt = p;
}
vector<int>tmp;
int w[M], nw[M];
ll sum, ans = 1e9;
void dfs1(int p, int fa)
{
	cnt[col[p]]++;
	tmp.push_back(p);
	if(fa)G[p].push_back(fa);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		dfs1(e[i], p);
	}
}
void dfs2(int p)
{
	if(tag[p])return;
	tag[p] = true;
	sum += nw[p];
	for(auto i : G[p])
		dfs2(i);
}
void solve(int p)
{
	getrt(p, 0);
	tot = sz[p], minn = 1e9;
	getrt(p, 0); p = rt;
	vis[p] = true;
	tmp.clear();
	dfs1(p, 0);
	map<int, bool>bib;
	for(auto i : tmp)
	{
		if(cnt[col[i]] < v[col[i]].size())
		{
			nw[i] = 1e9;
			continue;
		}
		nw[i] = w[i];
		if(!bib.count(col[i]))
		{
			bib[col[i]] = true;
			for(auto j : v[col[i]])
				G[col[i] + n].push_back(j);
		}
		G[i].push_back(col[i] + n);
	}
	sum = 0;
	dfs2(p);
	ans = min(ans, sum);
	for(auto i : tmp)
	{
		G[i].clear();
		G[col[i] + n].clear();
		tag[i] = tag[col[i] + n] = false;
		cnt[col[i]] = 0;
	}
	for(int i = h[p]; ~i; i = ne[i])
		if(!vis[e[i]])solve(e[i]);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		v[col[i]].push_back(i);
	}
	for(int i = 1; i <= k; i++)
		w[v[i].back()] = 1;
	solve(1);
	printf("%lld\n", ans - 1);
	return 0;
}
