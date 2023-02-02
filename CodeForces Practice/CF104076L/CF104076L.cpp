#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010, M = N << 1;
const int INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
int sz[N], msiz[N], dis[N];
int ans[N];
bool vis[N];
vector<pair<int, int>>dep, pos[N], q[N];
int rt;
void findrt(int p, int fa, int tot)
{
	msiz[p] = 0;
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		findrt(e[i], p, tot);
		sz[p] += sz[e[i]];
		msiz[p] = max(msiz[p], sz[e[i]]);
	}
	msiz[p] = max(msiz[p], tot - sz[p]);
	if(!rt || msiz[p] < msiz[rt])rt = p;
}
void getdis(int p, int fa, int d)
{
	dis[p] = d;
	dep.emplace_back(p, dis[p]);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		getdis(e[i], p, d + w[i]);
	}
}
int sta[N], tt;
void solve(int p)
{
	vis[p] = true, dis[p] = 0;
	dep.clear(), getdis(p, 0, 0);
	sort(dep.begin(), dep.end());
	int m = dep.size();
	tt = 0;
	for(int i = 0; i < m; i++)
	{
		while(tt && dep[i].second < dep[sta[tt]].second)tt--;
		if(tt)pos[dep[i].first].emplace_back(dep[sta[tt]].first, dep[i].second + dep[sta[tt]].second);
		sta[++tt] = i;
	}
	tt = 0;
	for(int i = m - 1; i >= 0; i--)
	{
		while(tt && dep[i].second < dep[sta[tt]].second)tt--;
		if(tt)pos[dep[sta[tt]].first].emplace_back(dep[i].first, dep[i].second + dep[sta[tt]].second);
		sta[++tt] = i;
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		rt = 0;
		findrt(e[i], p, sz[e[i]]);
		solve(rt);
	}
}
int tr[N];
#define lowbit(i) ((i)&-(i))
void add(int x, int c)
{
	for(int i = x; i; i -= lowbit(i))
		tr[i] = min(tr[i], c);
}
int qry(int x)
{
	int ans = INF;
	for(int i = x; i <= n; i += lowbit(i))
		ans = min(ans, tr[i]);
	return ans;
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	findrt(1, 0, n);
	solve(rt);
	scanf("%lld", &m);
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		if(x == y)ans[i] = -1;
		else q[y].emplace_back(x, i);
	}
	memset(tr, 63, sizeof(tr));
	for(int i = 1; i <= n; i++)
	{
		for(auto j : pos[i])
			add(j.first, j.second);
		for(auto j : q[i])
			ans[j.second] = qry(j.first);
	}
	for(int i = 1; i <= m; i++)
	{
		if(ans[i] == INF)puts("-1");
		else printf("%lld\n", ans[i]);
	}
	return 0;
}
