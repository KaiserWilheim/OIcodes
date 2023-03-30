#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
vector<pair<int, int>>v[N];
int ans[N];
int sz[N], tot;
int maxn, rt;
bool vis[N];
void getrt(int p, int fa)
{
	sz[p] = 1;
	int msiz = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		getrt(e[i], p);
		sz[p] += sz[e[i]];
		msiz = max(msiz, sz[e[i]]);
	}
	msiz = max(msiz, tot - sz[p]);
	if(!rt || msiz < maxn)maxn = msiz, rt = p;
}
int mdep;
int t[N], dep[N];
vector<pair<int, int>>q;
void getdis(int p, int fa)
{
	t[dep[p]]++;
	mdep = max(mdep, dep[p]);
	for(auto i : v[p])
	{
		if(i.first + 1 < dep[p])continue;
		q.emplace_back(i.first - dep[p] + 2, i.second);
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		dep[e[i]] = dep[p] + 1;
		getdis(e[i], p);
	}
}
void calc(int p)
{
	mdep = 0, q.clear();
	dep[p] = 1, getdis(p, 0);
	for(auto i : q)
		ans[i.second] += t[i.first];
	for(int i = 1; i <= mdep; i++)t[i] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		mdep = 0, q.clear();
		dep[e[i]] = 2, getdis(e[i], p);
		for(auto j : q)
			ans[j.second] -= t[j.first];
		for(int j = 1; j <= mdep; j++)t[j] = 0;
	}
}
void dfs(int p)
{
	calc(p);
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		maxn = 1e9, tot = sz[e[i]], rt = 0;
		getrt(e[i], 0);
		dfs(rt);
	}
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)v[i].clear();
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= m; i++)
	{
		int x, k;
		scanf("%d%d", &x, &k);
		v[x].emplace_back(k, i);
	}
	maxn = 1e9, tot = n;
	getrt(1, 0);
	dfs(rt);
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(h, -1, sizeof(h));
		memset(ans, 0, sizeof(ans));
		memset(vis, 0, sizeof(vis));
		idx = 0;
		solve();
	}
	return 0;
}
