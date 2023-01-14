#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int K = 110, N = 20010, M = N << 4;
const int INF = 1e9;
struct DSU
{
	int fa[N];
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
			fa[i] = i;
	}
	int find(int x)
	{
		if(fa[x] != x)fa[x] = find(fa[x]);
		return fa[x];
	}
	void soyuz(int x, int y)
	{
		int fx = find(x), fy = find(y);
		if(fx != fy)fa[fy] = fx;
	}
};
DSU dsu;
int n, m, k;
int S, T;
int h[N], e[M], ne[M], idx;
int f[M];
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}
int q[N], d[N], cur[N];
bool bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof(d));
	q[0] = S, d[S] = 0, cur[S] = h[S];
	while(hh <= tt)
	{
		int u = q[hh++];
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if(v == T)return true;
				q[++tt] = v;
			}
		}
	}
	return false;
}
int find(int u, int limit)
{
	if(u == T)return limit;
	int flow = 0;
	for(int i = cur[u]; ~i && flow < limit; i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], limit - flow));
			if(!t)d[v] = -1;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	return flow;
}
int dinic()
{
	int r = 0, flow;
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}
char s[K][K], tar[K][K];
int cnt;
int nw[N], col[N], a[N], b[N];
int id[K][K];
int dx[5] = { 1,0,-1,0 }, dy[5] = { 0,1,0,-1 };
bool vis[K][K];
bool chq(int x, int y)
{
	if(x < 1)return false;
	if(x > n)return false;
	if(y < 1)return false;
	if(y > m)return false;
	return true;
}
void bfs(int sx, int sy)
{
	queue<pair<int, int>>q;
	q.emplace(sx, sy);
	vis[sx][sy] = true;
	int rt = id[sx][sy];
	nw[rt] = ++cnt, col[cnt] = s[sx][sy] - '0';
	while(!q.empty())
	{
		auto now = q.front();
		q.pop();
		int x = now.first, y = now.second;
		if(s[sx][sy] == tar[x][y])b[cnt]++;
		else a[cnt]++;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(!chq(nx, ny) || vis[nx][ny] || s[x][y] != s[nx][ny])continue;
			q.emplace(nx, ny);
			vis[nx][ny] = true;
			dsu.soyuz(rt, id[nx][ny]);
		}
	}
}
set<pair<int, int>>bib;
vector<int>G[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++)
		scanf("%s", tar[i] + 1);
	dsu.init(n * m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			id[i][j] = ++cnt;
	S = 0, T = 1, cnt = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(!vis[i][j])bfs(i, j);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			for(int d = 0; d < 4; d++)
			{
				int nx = i + dx[d], ny = j + dy[d];
				if(!chq(nx, ny) || s[nx][ny] == s[i][j])continue;
				int u = dsu.find(id[i][j]), v = dsu.find(id[nx][ny]);
				u = nw[u], v = nw[v];
				if(u > v)swap(u, v);
				if(!bib.count(make_pair(u, v)))
				{
					G[u].push_back(v);
					G[v].push_back(u);
					bib.emplace(u, v);
				}
			}
		}
	}
	for(int i = 2; i <= cnt; i++)
	{
		if(col[i] == 0)add(S, i, a[i]), add(i, T, b[i]);
		else add(S, i, b[i]), add(i, T, a[i]);
	}
	for(int i = 2; i <= cnt; i++)
	{
		if(col[i] == 1)continue;
		for(auto j : G[i])
			add(i, j, INF);
	}
	printf("%d\n", dinic());
	return 0;
}
