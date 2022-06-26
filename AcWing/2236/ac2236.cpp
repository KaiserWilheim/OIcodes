#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 400010;
const int INF = 1e9;
int n, m;
int S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
bool vis_s[N], vis_t[N];
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
void dfs(int p, bool vis[], int t)
{
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i], v = i ^ t;
		if(f[v] && !vis[j])
			dfs(j, vis, t);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	S = 0, T = n - 1;
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
	dinic();
	dfs(S, vis_s, 0);
	dfs(T, vis_t, 1);
	int res = 0;
	for(int i = 0; i < m * 2; i += 2)
		if(!f[i] && vis_s[e[i ^ 1]] && vis_t[e[i]])
			res++;
	printf("%d\n", res);
	return 0;
}
