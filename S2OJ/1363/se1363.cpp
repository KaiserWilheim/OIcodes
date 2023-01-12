#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const int INF = 1e9;
int n, m;
int S, T;
int a[N];
int h[N], e[M], ne[M], f[M], idx;
void add(int a, int b, int c,int d)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = d, ne[idx] = h[b], h[b] = idx++;
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
int cnt;
int pr[N];
void solve()
{
	memset(h, -1, sizeof(h));
	memset(pr, 0, sizeof(pr));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	S = 0;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(pr[u], ++cnt, pr[u] ? a[u] : 1, 0), pr[u] = cnt;
		add(pr[v], ++cnt, pr[v] ? a[v] : 1, 0), pr[v] = cnt;
		add(pr[u], pr[v], 1, 1);
	}
	T = cnt + 1;
	add(pr[1], T, a[1], 0);
	printf("%d\n", dinic());
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = 0;
		cnt = 0;
		solve();
	}
	return 0;
}
