#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 400010;
const int INF = 1e9;
int m, n;
int S, T, s, t;
int h[N], e[M], ne[M], f[M], l[M], idx;
int A[N];
int q[N], d[N], cur[N];
void add(int a, int b, int c, int d)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = d - c, l[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
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
	scanf("%d%d", &s, &t);
	S = 0, T = n + 1;
	for(int i = 1; i <= m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		add(a, b, c, d);
		A[a] -= c, A[b] += c;
	}
	int tot = 0;
	for(int i = 1; i <= n; i++)
	{
		if(A[i] > 0)
		{
			add(S, i, 0, A[i]);
			tot += A[i];
		}
		else if(A[i] < 0)
		{
			add(i, T, 0, -A[i]);
		}
	}
	add(t, s, 0, INF);
	int res = dinic();
	if(res != tot)puts("No Solution");
	else
	{
		res = f[idx - 1];
		f[idx - 1] = f[idx - 2] = 0;
		S = t, T = s;
		int ans = res - dinic();
		printf("%d\n", ans);
	}
	return 0;
}
