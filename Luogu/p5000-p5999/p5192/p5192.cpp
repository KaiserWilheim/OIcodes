#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 1000010;
const int INF = 1e9;
int n, m;
int S, T, s, t;
int h[N], e[M], ne[M], f[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
}
int d[N];
bool bfs()
{
	queue<int>q;
	memset(d, -1, sizeof(d));
	q.push(S), d[S] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				if(v == T)return true;
				q.push(v);
			}
		}
	}
	return false;
}
int find(int u, int lim)
{
	if(u == T)return lim;
	int flow = 0;
	for(int i = h[u]; ~i && flow < lim; i = ne[i])
	{
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], lim - flow));
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
int A[N];
int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		memset(h, -1, sizeof(h));
		memset(A, 0, sizeof(A));
		idx = 0;
		s = 0, t = n + m + 1;
		S = n + m + 2, T = n + m + 3;
		for(int i = 1; i <= m; i++)
		{
			int g;
			scanf("%d", &g);
			add(i + n, t, INF);
			A[i + n] -= g, A[t] += g;
		}
		for(int i = 1; i <= n; i++)
		{
			int c, d;
			scanf("%d%d", &c, &d);
			add(s, i, d);
			for(int j = 1; j <= c; j++)
			{
				int t, l, r;
				scanf("%d%d%d", &t, &l, &r);
				t++;
				add(i, t + n, r - l);
				A[i] -= l, A[t + n] += l;
			}
		}
		int tot = 0;
		for(int i = 1; i <= n + m + 2; i++)
		{
			if(A[i] > 0)
			{
				add(S, i, A[i]);
				tot += A[i];
			}
			else if(A[i] < 0)add(i, T, -A[i]);
		}
		add(t, s, INF);
		int res = dinic();
		if(res != tot)puts("-1");
		else
		{
			res = f[idx - 1];
			f[idx - 1] = f[idx - 2] = 0;
			S = s, T = t;
			int ans = res + dinic();
			printf("%d\n", ans);
		}
		putchar('\n');
	}
	return 0;
}
