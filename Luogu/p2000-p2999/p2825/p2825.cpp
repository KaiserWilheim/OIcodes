#include <bits/stdc++.h>
using namespace std;
const int N = 1010, M = 20010;
const int INF = 1e9;
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
char s[N][N];
int col[N][N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	int totc = 0, totr = 0;
	for(int i = 1; i <= n; i++)
		cin >> s[i] + 1;
	for(int i = 1; i <= m; i++)
	{
		bool flag = false;
		totc++;
		for(int j = 1; j <= n; j++)
		{
			if(s[j][i] == '#' && flag == true)
			{
				flag = false;
				totc++;
			}
			if(s[j][i] == '*')
			{
				flag = true;
				col[j][i] = totc;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		bool flag = false;
		totr++;
		for(int j = 1; j <= m; j++)
		{
			if(s[i][j] == '#' && flag == true)
			{
				flag = false;
				totr++;
			}
			if(s[i][j] == '*')
			{
				flag = true;
				add(col[i][j], totr + totc, 1);
			}
		}
	}
	S = 0, T = totr + totc + 1;
	for(int i = 1; i <= totc; i++)
		add(S, i, 1);
	for(int i = 1; i <= totr; i++)
		add(i + totc, T, 1);
	int ans = dinic();
	printf("%d\n", ans);
	return 0;
}