#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = 400010;
int n, m, s, t;
struct DSU
{
	int fa[N];
	void init(int n)
	{
		for(int i = 1; i <= n; i++)fa[i] = i;
	}
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
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int deg[N];
bool safe[N];
int dis[2][N];
void bfs(int s, int ty)
{
	queue<int>q;
	dis[ty][s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[ty][v] != 1e9)continue;
			dis[ty][v] = dis[ty][u] + 1;
			q.push(v);
		}
	}
}
void solve(int id)
{
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);
	for(int i = 1; i <= n; i++)
	{
		h[i] = -1;
		deg[i] = 0;
		safe[i] = true;
		dis[0][i] = dis[1][i] = 1e9;
	}
	dsu.init(n);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
		dsu.soyuz(u, v);
		deg[v]++, deg[u]++;
	}
	if(dsu.find(s) != dsu.find(t))
	{
		printf("Case #%d: SAFE\n", id);
		return;
	}
	queue<int>q;
	for(int i = 1; i <= n; i++)
		if(deg[i] == 1)q.push(i);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		safe[u] = false;
		for(int i = h[u]; ~i; i = ne[i])
		{
			deg[e[i]]--;
			if(deg[e[i]] == 1)q.push(e[i]);
		}
	}
	bfs(s, 0);
	bfs(t, 1);
	bool flag = false;
	for(int i = 1; i <= n; i++)
	{
		if(!safe[i])continue;
		if(dis[0][i] < dis[1][i])flag = true;
	}
	if(flag)
	{
		printf("Case #%d: SAFE\n", id);
		return;
	}
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		if(dis[0][i] >= dis[1][i])continue;
		maxn = max(maxn, dis[1][i]);
	}
	printf("Case #%d: %d\n", id, maxn * 2);
}
int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
	{
		idx = 0;
		solve(i);
	}
	return 0;
}
