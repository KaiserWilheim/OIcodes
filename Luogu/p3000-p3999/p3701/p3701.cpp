#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = 200010, INF = 1e9;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
string s1[N], s2[N];

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
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}

int main()
{
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof(h));
	S = 0, T = n * 2 + 1;
	int sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; i++)
	{
		cin >> s1[i];
		if(s1[i] == "YYY")sum1++;
	}
	for(int i = 1; i <= n; i++)
	{
		cin >> s2[i];
		if(s2[i] == "YYY")sum2++;
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if(s1[i] == "J")x += sum1;
		add(S, i, x);
		for(int j = 1; j <= n; j++)
		{
			if(s1[i] == "J")
			{
				if(s2[j] == "HK" || s2[j] == "W")
					add(i, j + n, 1);
			}
			else if(s1[i] == "E")
			{
				if(s2[j] == "YYY" || s2[j] == "J")
					add(i, j + n, 1);
			}
			else if(s1[i] == "YYY")
			{
				if(s2[j] == "J" || s2[j] == "HK")
					add(i, j + n, 1);
			}
			else if(s1[i] == "HK")
			{
				if(s2[j] == "E" || s2[j] == "W")
					add(i, j + n, 1);
			}
			else if(s1[i] == "W")
			{
				if(s2[j] == "YYY" || s2[j] == "E")
					add(i, j + n, 1);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if(s2[i] == "J")x += sum2;
		add(i + n, T, x);
	}
	printf("%d\n", min(m, dinic()));
	return 0;
}
