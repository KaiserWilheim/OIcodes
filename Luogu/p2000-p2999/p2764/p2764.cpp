#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 4;
const int INF = 1e9;
int n, m;
int S, T;
int h[N], e[M], ne[M], idx;
int f[M];
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}
int q[N], d[N], cur[N];
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
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}
int fa[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
void output(int x)
{
	printf("%d ", x);
	for(int i = h[x]; ~i; i = ne[i])
	{
		if(f[i] == 0 && e[i] > n)
			output(e[i] - n);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	S = 0, T = 2 * n + 1;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v + n, 1);
	}
	for(int i = 1; i <= n; i++)add(S, i, 1), add(i + n, T, 1);
	int ans = n - dinic();
	for(int i = 1; i <= n; i++)fa[i] = i;
	for(int u = 1; u <= n; u++)
	{
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(e[i] <= n)continue;
			if(f[i] != 0)continue;
			int fu = find(u), fv = find(e[i] - n);
			fa[fv] = fu;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)
		{
			output(i);
			putchar('\n');
		}
	}
	printf("%d\n", ans);
	return 0;
}
