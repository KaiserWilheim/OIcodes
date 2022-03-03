#include<bits/stdc++.h>
using namespace std;
const int N = 10010, M = 200010, INF = 1e8;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];


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


int main()
{
	int room, meal;
	scanf("%d%d%d", &n, &room, &meal);
	memset(h, -1, sizeof h);
	S = 0, T = n * 2 + room + meal + 1;
	for(int i = 1; i <= room; i++)
		add(S, i, 1);
	for(int i = 1; i <= meal; i++)
		add(i + room + n * 2, T, 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= room; j++)
		{
			int x;
			scanf("%d", &x);
			if(x == 1)
				add(j, i + room, 1);
		}
		add(i + room, i + room + n, 1);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= meal; j++)
		{
			int x;
			scanf("%d", &x);
			if(x == 1)
				add(i + room + n, j + room + n * 2, 1);
		}
	}
	printf("%d\n", dinic());
	return 0;
}
