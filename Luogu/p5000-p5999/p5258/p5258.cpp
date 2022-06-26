#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 800010;
const int INF = 1e9;
int n, m;
int S, T;
int s, t;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
int A[N];
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	s = n, t = n + 1;
	S = n + 2, T = n + 3;
	for(int i = 1; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(y, x, INF - 1);
		A[y]--, A[x]++;
	}
	for(int i = 0; i < n; i++)
	{
		add(s, i, INF);
		add(i, t, INF);
	}
	int tot = 0;
	for(int i = 0; i < n; i++)
	{
		if(A[i] > 0)
		{
			add(S, i, A[i]);
			tot += A[i];
		}
		else if(A[i] < 0)
		{
			add(i, T, -A[i]);
		}
	}
	add(t, s, INF);
	dinic();
	int res = f[idx - 1];
	f[idx - 1] = f[idx - 2] = 0;
	S = t, T = s;
	res -= dinic();
	printf("%d\n", res);
	return 0;
}
