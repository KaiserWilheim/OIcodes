#include<bits/stdc++.h>
using namespace std;
const int N = 40010, M = 800010, INF = 1e8;
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
	while(bfs())
		while(flow = find(S, INF)) r += flow;
	return r;
}


int main()
{
	int prac, answ;
	scanf("%d%d%d", &n, &prac, &answ);
	memset(h, -1, sizeof h);
	S = 0, T = n * 2 + prac + answ + 1;
	for(int i = 1; i <= prac; i++)
		add(S, i, 1);
	for(int i = 1; i <= answ; i++)
		add(i + prac + n * 2, T, 1);
	int m;
	scanf("%d", &m);
	while(m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(b, a + prac, 1);
	}
	scanf("%d", &m);
	while(m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a + prac + n, b + n * 2 + prac, 1);
	}
	for(int i = 1; i <= n; i++)
		add(i + prac, i + prac + n, 1);
	printf("%d\n", dinic());
	return 0;
}
