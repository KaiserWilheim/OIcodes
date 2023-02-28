#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int n, m;
int g, maxn, minn;
int indeg[N];
int h[N], hs[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, ne[idx] = hs[b], hs[b] = idx++;
}
struct DSU
{
	int fa[N];
	void init(int n) { for(int i = 0; i <= n; i++)fa[i] = i; }
	int find(int x)
	{
		if(fa[x] != x)fa[x] = find(fa[x]);
		return fa[x];
	}
	void soyuz(int u, int v)
	{
		int fu = find(u), fv = find(v);
		if(fu != fv)fa[fu] = fv;
	}
};
DSU dsu;
bool vis[N];
int dis[N], bl[N];
int len[N];
void dfs(int p, int t)
{
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(bl[e[i]] == t)g = gcd(g, abs(dis[p] + 1 - dis[e[i]]));
		dis[e[i]] = dis[p] + 1;
		maxn = max(maxn, dis[e[i]]);
		bl[e[i]] = t;
		if(!vis[e[i]])dfs(e[i], t);
	}
	for(int i = hs[p]; ~i; i = ne[i])
	{
		if(bl[e[i]] == t)g = gcd(g, abs(dis[p] - 1 - dis[e[i]]));
		dis[e[i]] = dis[p] - 1;
		minn = min(minn, dis[e[i]]);
		bl[e[i]] = t;
		if(!vis[e[i]])dfs(e[i], t);
	}
}
void solve()
{
	memset(h, -1, sizeof(h));
	memset(hs, -1, sizeof(hs));
	memset(vis, 0, sizeof(vis));
	memset(bl, 0, sizeof(bl));
	g = 0;
	n = read(), m = read();
	dsu.init(n);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		u = read() + 1, v = read() + 1;
		add(u, v);
		dsu.soyuz(u, v);
	}
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			dis[i] = 0;
			maxn = minn = 0;
			bl[i] = i, dfs(i, i);
			len[dsu.find(i)] = maxn - minn;
		}
	}
	bool flag = false;
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			flag = true;
			break;
		}
	}
	if(!flag && !g)
	{
		for(int i = 1; i <= n; i++)
			if(dsu.find(i) == i)g += len[i];
		printf("%d\n", n - g);
		return;
	}
	for(int i = 1; i <= n; i++)
		if(!vis[i])bl[i] = i, dfs(i, i);
	printf("%d\n", n - g);

}
int main()
{
	int T = read();
	while(T--)
	{
		idx = 0;
		solve();
	}
	return 0;
}
