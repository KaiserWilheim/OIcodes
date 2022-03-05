#include<bits/stdc++.h>
using namespace std;
#define pfin (x-1)*m+y
#define pfout (x-1)*m+y+n*m
const int N = 1010, M = 200010, INF = 1e8;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int dis, tot;
char reich[N][N], volke[N][N];

void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof d);
	q[0] = S, d[S] = 0, cur[S] = h[S];
	while(hh <= tt)
	{
		int t = q[hh++];
		for(int i = h[t]; ~i; i = ne[i])
		{
			int ver = e[i];
			if(d[ver] == -1 && f[i])
			{
				d[ver] = d[t] + 1;
				cur[ver] = h[ver];
				if(ver == T)  return true;
				q[++tt] = ver;
			}
		}
	}
	return false;
}

int find(int u, int limit)
{
	if(u == T) return limit;
	int flow = 0;
	for(int i = cur[u]; ~i && flow < limit; i = ne[i])
	{
		cur[u] = i;
		int ver = e[i];
		if(d[ver] == d[u] + 1 && f[i])
		{
			int t = find(ver, min(f[i], limit - flow));
			if(!t) d[ver] = -1;
			f[i] -= t, f[i ^ 1] += t, flow += t;
		}
	}
	return flow;
}

int dinic()
{
	int r = 0, flow;
	while(bfs())
		while(flow = find(S, INF)) r += flow;
	return r;
}

void link(int u, int x, int y)
{
	if((x < 1) || (x > n) || (y < 1) || (y > m))
	{
		add(u, T, INF);
		return;
	}
	if(reich[x][y] == '0')return;
	add(u, pfin, INF);
	return;
}
void connect(int x, int y)
{
	if(reich[x][y] == '0')return;
	add(pfin, pfout, reich[x][y] - '0');
	if(volke[x][y] == 'L')
	{
		add(S, pfin, 1);
		tot++;
	}
	if((x == 1) || (x == n) || (y == 1) || (y == m))
		add(pfout, T, INF);
	int u = pfout;
	if(dis >= 1)
	{
		link(u, x - 1, y);
		link(u, x + 1, y);
		link(u, x, y - 1);
		link(u, x, y + 1);
	}
	if(dis >= 2)
	{
		link(u, x - 2, y);
		link(u, x + 2, y);
		link(u, x, y - 2);
		link(u, x, y + 2);
		link(u, x - 1, y - 1);
		link(u, x + 1, y - 1);
		link(u, x - 1, y + 1);
		link(u, x + 1, y + 1);
	}
	if(dis >= 3)
	{
		link(u, x - 3, y);
		link(u, x + 3, y);
		link(u, x, y - 3);
		link(u, x, y + 3);
		link(u, x - 2, y - 1);
		link(u, x + 2, y - 1);
		link(u, x - 2, y + 1);
		link(u, x + 2, y + 1);
		link(u, x - 1, y - 2);
		link(u, x + 1, y - 2);
		link(u, x - 1, y + 2);
		link(u, x + 1, y + 2);
		link(u, x - 2, y - 2);
		link(u, x + 2, y - 2);
		link(u, x - 2, y + 2);
		link(u, x + 2, y + 2);
	}
	if(dis >= 4)
	{
		link(u, x - 4, y);
		link(u, x + 4, y);
		link(u, x, y - 4);
		link(u, x, y + 4);
		link(u, x - 3, y - 1);
		link(u, x + 3, y - 1);
		link(u, x - 3, y + 1);
		link(u, x + 3, y + 1);
		link(u, x - 1, y - 3);
		link(u, x + 1, y - 3);
		link(u, x - 1, y + 3);
		link(u, x + 1, y + 3);
		link(u, x - 3, y - 2);
		link(u, x + 3, y - 2);
		link(u, x - 3, y + 2);
		link(u, x + 3, y + 2);
		link(u, x - 2, y - 3);
		link(u, x + 2, y - 3);
		link(u, x - 2, y + 3);
		link(u, x + 2, y + 3);
	}
	return;
}

int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &dis);
	S = 0, T = n * m * 2 + 1;
	for(int i = 1; i <= n; i++)scanf("%s", reich[i] + 1);
	for(int i = 1; i <= n; i++)scanf("%s", volke[i] + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			connect(i, j);
	printf("%d\n", tot - dinic());
	return 0;
}
