#include <bits/stdc++.h>
using namespace std;
const int N = 10010, M = 2000010;
const int INF = 1e9;
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
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[t] + 1;
				cur[v] = h[v];
				if(v == T)  return true;
				q[++tt] = v;
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
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], limit - flow));
			if(!t) d[v] = -1;
			f[i] -= t, f[i ^ 1] += t, flow += t;
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	S = 0, T = 5001;
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		sum += x;
		add(S, i, x);
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		sum += x;
		add(i, T, x);
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int k, c1, c2;
		scanf("%d%d%d", &k, &c1, &c2);
		add(S, n + i * 2 - 1, c1);
		add(n + i * 2, T, c2);
		sum += c1 + c2;
		for(int j = 1; j <= k; j++)
		{
			int x;
			scanf("%d", &x);
			add(n + i * 2 - 1, x, INF);
			add(x, n + i * 2, INF);
		}
	}
	printf("%d\n", sum - dinic());
	return 0;
}
