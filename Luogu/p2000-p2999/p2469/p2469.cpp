#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 200010;
const int INF = 1e9;
int m, n;
int S, T;
int h[N], e[M], ne[M], f[M], w[M], idx;
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
	while (hh != tt)
	{
		int t = q[hh++];
		if (hh == N) hh = 0;
		st[t] = false;

		for (int i = h[t]; ~i; i = ne[i])
		{
			int ver = e[i];
			if (f[i] && d[ver] > d[t] + w[i])
			{
				d[ver] = d[t] + w[i];
				pre[ver] = i;
				incf[ver] = min(f[i], incf[t]);
				if (!st[ver])
				{
					q[tt++] = ver;
					if (tt == N) tt = 0;
					st[ver] = true;
				}
			}
		}
	}
	return incf[T] > 0;
}

void EK(int& flow, int& cost)
{
	flow = cost = 0;
	while (spfa())
	{
		int t = incf[T];
		flow += t, cost += t * d[T];
		for (int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	S = 0, T = n * 2 + 1;
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		add(S, i, 1, 0);
		add(S, i + n, 1, a);
		add(i + n, T, 1, 0);
	}
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a > b)swap(a, b);
		add(a, b + n, 1, c);
	}
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", cost);
	return 0;
}