#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20010, M = 40010;
const int INF = 1e9;
int n, m, k;
int S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
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
	scanf("%d%d", &n, &m);
	S = 0, T = n + m + 1;
	int tot = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(S, i, x);
		tot += x;
	}
	for(int i = 1; i <= m; i++)
	{
		add(i + n, T, 1);
		int p;
		scanf("%d", &p);
		while(p--)
		{
			int x;
			scanf("%d", &x);
			add(x, i + n, 1);
		}
	}
	int res = dinic();
	if(res != tot)
	{
		puts("No Solution!");
		return 0;
	}
	for(int p = 1; p <= n; p++)
	{
		printf("%d: ", p);
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(e[i] == S)continue;
			if(f[i ^ 1] > 0)printf("%d ", e[i] - n);
		}
		putchar('\n');
	}
	return 0;
}
