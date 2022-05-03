#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = N * N * 2, INF = 1e9;
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
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}

set<pair<int, int> >dic;

int main()
{
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof(h));
	S = 0, T = m + n + 1;
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(S, i, x);
		sum += x;
	}
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		add(i + n, T, x);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			add(i, j + n, 1);
	int flow = dinic();
	if(flow < sum)
	{
		puts("0");
		return 0;
	}
	else
	{
		puts("1");
		for(int i = 1; i <= n; i++)
		{
			for(int j = h[i]; ~j; j = ne[j])
			{
				int v = e[j];
				if(v != S && f[j ^ 1])
					printf("%d ", v - n);
			}
			puts("");
		}
	}
	return 0;
}
