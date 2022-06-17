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
int b[N], r[N];
int prime[N];
bool visit[N];
void sieve()
{
	for(int i = 2; i <= 10001; i++)
	{
		if(!visit[i])
		{
			if(10001 < i * i)break;
			for(int j = i * i; j <= 10001; j += i)visit[j] = true;
		}
	}
	for(int i = 2; i <= 10001; i++)
		if(!visit[i])prime[++prime[0]] = i;
}
void solve()
{
	scanf("%d%d", &n, &m);
	S = 0, T = n + m + prime[0] + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		add(S, i, 1);
		for(int j = 1; j <= prime[0] && prime[j] <= b[i]; j++)
			if(b[i] % prime[j] == 0)add(i, j + n, 1);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &r[i]);
		add(i + n + prime[0], T, 1);
		for(int j = 1; j <= prime[0] && prime[j] <= r[i]; j++)
			if(r[i] % prime[j] == 0)add(j + n, i + prime[0] + n, 1);
	}
	printf("%d\n", dinic());
}
int main()
{
	sieve();
	int test_num;
	scanf("%d", &test_num);
	while(test_num--)
	{
		memset(h, -1, sizeof(h));
		idx = 0;
		solve();
	}
	return 0;
}
