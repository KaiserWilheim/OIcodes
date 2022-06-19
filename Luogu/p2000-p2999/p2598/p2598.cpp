#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 100010;
const int INF = 1e9;
int n, m, k;
int S, T;
int h[N], e[M], ne[M], idx;
int f[M];
int q[N], d[N], cur[N];
void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = d, ne[idx] = h[b], h[b] = idx++;
}
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
	while(bfs())while(flow = find(S, INF))r += flow;
	return r;
}
#define get(i,j) (i-1)*m+j
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	S = 0, T = n * m + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int x;
			scanf("%d", &x);
			if(x == 1)add(S, get(i, j), INF, 0);
			else if(x == 2)add(get(i, j), T, INF, 0);
			if(i != n)add(get(i, j), get(i + 1, j), 1, 1);
			if(j != m)add(get(i, j), get(i, j + 1), 1, 1);
		}
	}
	printf("%d\n", dinic());
	return 0;
}
