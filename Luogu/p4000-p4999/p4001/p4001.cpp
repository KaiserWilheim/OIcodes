#include <bits/stdc++.h>
using namespace std;
#define ll long long
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') { f = -1; } c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
const int N = 1000010, M = 10000010;
const int INF = 1e8;
int n, m;
int S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

bool bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof(d));
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
#define get(i,j) (i-1)*m+j
int main()
{
	memset(h, -1, sizeof(h));
	n = read(), m = read();
	S = 1, T = get(n, m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < m; j++)
		{
			int k = read();
			add(get(i, j), get(i, j + 1), k);
		}
	for(int i = 1; i < n; i++)
		for(int j = 1; j <= m; j++)
		{
			int k = read();
			add(get(i, j), get(i + 1, j), k);
		}
	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++)
		{
			int k = read();
			add(get(i, j), get(i + 1, j + 1), k);
		}
	printf("%d\n", dinic());
	return 0;
}
