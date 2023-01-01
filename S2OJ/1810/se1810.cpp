#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 600010, M = N << 1;
const int INF = 1e9;
#define id(i,j,k) ((k)*n*m+((i)-1)*m+(j))
int n, m;
int S, T;
int a[60][60];
int h[N], e[M], ne[M], f[M], idx;
ll ans;
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}
int d[N], cur[N];
bool bfs()
{
	queue<int>q;
	memset(d, -1, sizeof(d));
	d[S] = 0, cur[S] = h[S];
	q.push(S);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if(v == T)return true;
				q.push(v);
			}
		}
	}
	return false;
}
int find(int u, int lim)
{
	if(u == T)return lim;
	int flow = 0;
	for(int i = cur[u]; ~i && flow < lim; i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(lim - flow, f[i]));
			if(!t)d[v] = -1;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	return flow;
}
int dinic()
{
	int res = 0, flow;
	while(bfs())while(flow = find(S, INF))res += flow;
	return res;
}
int dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 };
bool chq(int x, int y)
{
	if(x < 1)return false;
	if(x > n)return false;
	if(y < 1)return false;
	if(y > m)return false;
	return true;
}
void insert(int X, int Y, int flag)
{
	int maxn = 0;
	int x = X, y = Y;
	while(chq(x, y))
	{
		maxn = max(maxn, a[x][y]);
		x += dx[flag], y += dy[flag];
	}
	if(!maxn)return;
	x = X, y = Y;
	if(flag == 3 || flag == 4)
	{
		add(S, id(x, y, 0), INF);
		while(chq(x, y))
		{
			int nx = x + dx[flag], ny = y + dy[flag];
			add(id(x, y, 0), id(nx, ny, 0), maxn - max(0, a[x][y]));
			x = nx, y = ny;
		}
	}
	else
	{
		add(id(x, y, 1), T, INF);
		while(chq(x, y))
		{
			int nx = x + dx[flag], ny = y + dy[flag];
			add(id(nx, ny, 1), id(x, y, 1), maxn - max(0, a[x][y]));
			x = nx, y = ny;
		}
	}
	ans += maxn;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	S = 2 * n * m + 1, T = 2 * n * m + 2;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			add(id(i, j, 0), id(i, j, 1), INF);
			if(a[i][j] == -1)insert(i, j, 1);
			if(a[i][j] == -2)insert(i, j, 2);
			if(a[i][j] == -3)insert(i, j, 3);
			if(a[i][j] == -4)insert(i, j, 4);
		}
	}
	printf("%lld\n", ans - dinic());
	return 0;
}