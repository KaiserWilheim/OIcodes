#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4010, M = 4000010, INF = 1e9;
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
	scanf("%d%d", &n, &m);
	S = 0, T = n + m + 1;
	int tot = 0;
	for(int i = 1; i <= n; i++)
	{
		int k,t;
		scanf("%d%d", &k, &t);
		add(S, i, k);
		tot += k;
		for(int j = 1; j <= t; j++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			add(i, a + n, b);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int k;
		scanf("%d", &k);
		add(i + n, T, k);
	}
	int flow = dinic();
	printf("%d\n", tot - flow);
	return 0;
}
