#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4010, M = 4000010, INF = 1e9;
int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}
bool spfa()
{
	int hh = 0, tt = 1;
	memset(d, 0x3f, sizeof d);
	memset(incf, 0, sizeof incf);
	q[0] = S, d[S] = 0, incf[S] = INF;
	while(hh != tt)
	{
		int t = q[hh++];
		if(hh == N) hh = 0;
		st[t] = false;

		for(int i = h[t]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[i] && d[v] > d[t] + w[i])
			{
				d[v] = d[t] + w[i];
				pre[v] = i;
				incf[v] = min(f[i], incf[t]);
				if(!st[v])
				{
					q[tt++] = v;
					if(tt == N) tt = 0;
					st[v] = true;
				}
			}
		}
	}

	return incf[T] > 0;
}
void EK(int &flow, int &cost)
{
	flow = cost = 0;
	while(spfa())
	{
		int t = incf[T];
		flow += t, cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &m, &n);
	S = 0, T = n + n * m + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int x;
			scanf("%d", &x);
			for(int k = 1; k <= n; k++)
				add(i, j * n + k, 1, x * k);
		}
	}
	for(int i = 1; i <= n; i++)add(S, i, 1, 0);
	for(int i = 1; i <= n * m; i++)add(i + n, T, 1, 0);
	int flow, cost;
	EK(flow, cost);
	printf("%.2lf\n", (double)cost / n);
	return 0;
}
