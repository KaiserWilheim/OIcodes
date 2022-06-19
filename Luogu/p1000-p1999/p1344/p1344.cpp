#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 100010;
const ll INF = 1e15;
int n, m, k;
int S, T;
int h[N], e[M], ne[M], idx;
ll f[M];
int q[N], d[N], cur[N];
void add(int a, int b, ll c)
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
ll find(int u, ll limit)
{
	if(u == T)return limit;
	ll flow = 0;
	for(int i = cur[u]; ~i && flow < limit; i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			ll t = find(v, min(f[i], limit - flow));
			if(!t)d[v] = -1;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	return flow;
}
ll dinic()
{
	ll r = 0, flow;
	while(bfs())while(flow = find(S, INF))r += flow;
	return r;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	ll delta = 13331;
	S = 1, T = n;
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		ll c;
		scanf("%d%d%lld", &a, &b, &c);
		add(a, b, c * delta + 1);
	}
	ll res = dinic();
	printf("%lld %lld\n", res / delta, res % delta);
	return 0;
}
