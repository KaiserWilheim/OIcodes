#include<bits/stdc++.h>
using namespace std;
const int N = 5010, M = 100010, INF = 1e8;
int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
int nums[160][160], sum[160];

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
			int ver = e[i];
			if(f[i] && d[ver] > d[t] + w[i])
			{
				d[ver] = d[t] + w[i];
				pre[ver] = i;
				incf[ver] = min(f[i], incf[t]);
				if(!st[ver])
				{
					q[tt++] = ver;
					if(tt == N) tt = 0;
					st[ver] = true;
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
	scanf("%d%", &n);
	memset(h, -1, sizeof h);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &nums[i][j]);
			sum[i] += nums[i][j];
		}
	}
	S = 0, T = 2 * n + 1;
	for(int i = 1; i <= n; i++)
	{
		add(S, i, 1, 0);
		add(i + n, T, 1, 0);
		for(int j = 1; j <= n; j++)
			add(i, j + n, 1, sum[i] - nums[i][j]);
	}
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", cost);
	return 0;
}
