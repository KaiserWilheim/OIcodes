#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 400010;
const int INF = 1e9;
int n, m;
int id(int i, int j) { return (i - 1) * m + j; }
int S, T;
int h[N], e[M], ne[M], f[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
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
int dx[5] = { 1,0,-1,0 }, dy[5] = { 0,1,0,-1 };
bool chq(int x, int y)
{
	if(x < 1)return false;
	if(x > n)return false;
	if(y < 1)return false;
	if(y > m)return false;
	return true;
}
int main()
{
	memset(h, -1, sizeof(h));
	int sum = 0;
	scanf("%d%d", &n, &m);
	S = 0, T = n * m + 1;
	int bib = n * m + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			sum += tmp;
			add(S, id(i, j), tmp);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			sum += tmp;
			add(id(i, j), T, tmp);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			sum += tmp;
			bib++;
			add(S, bib, tmp);
			add(bib, id(i, j), INF);
			for(int k = 0; k < 4; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				if(chq(nx, ny))add(bib, id(nx, ny), INF);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			sum += tmp;
			bib++;
			add(bib, T, tmp);
			add(id(i, j), bib, INF);
			for(int k = 0; k < 4; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				if(chq(nx, ny))add(id(nx, ny), bib, INF);
			}
		}
	}
	sum -= dinic();
	printf("%d\n", sum);
	return 0;
}
