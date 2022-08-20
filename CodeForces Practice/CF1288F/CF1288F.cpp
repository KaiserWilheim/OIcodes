#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010, M = 200010;
const int INF = 1e9;
int m, n1, n2;
int S, T, s, t;
int R, B;
int h[N], e[M], f[M], w[M], ne[M], idx;
int A[N], tot;
int q[N], d[N], pre[N], incf[N];
bool st[N];
void add(int a, int b, int l, int r, int c)
{
	A[a] -= l, A[b] += l;
	e[idx] = b, f[idx] = r - l, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -c, ne[idx] = h[b], h[b] = idx++;
}
bool spfa()
{
	int hh = 0, tt = 1;
	memset(d, 0x3f, sizeof(d));
	memset(incf, 0, sizeof(incf));
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
	scanf("%d%d%d%d%d", &n1, &n2, &m, &R, &B);
	s = 0, t = n1 + n2 + 1;
	S = n1 + n2 + 2, T = n1 + n2 + 3;
	string lc, rc;
	cin >> lc >> rc;
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b + n1, 0, 1, R);
		add(b + n1, a, 0, 1, B);
	}
	for(int i = 1; i <= n1; i++)
	{
		if(lc[i - 1] == 'R')add(s, i, 1, INF, 0);
		if(lc[i - 1] == 'B')add(i, t, 1, INF, 0);
		if(lc[i - 1] == 'U')add(s, i, 0, INF, 0), add(i, t, 0, INF, 0);
	}
	for(int i = 1; i <= n2; i++)
	{
		if(rc[i - 1] == 'R')add(i + n1, t, 1, INF, 0);
		if(rc[i - 1] == 'B')add(s, i + n1, 1, INF, 0);
		if(rc[i - 1] == 'U')add(s, i + n1, 0, INF, 0), add(i + n1, t, 0, INF, 0);
	}
	add(t, s, 0, INF, 0);
	for(int i = s; i <= t; i++)
	{
		if(A[i] > 0)tot += A[i], add(S, i, 0, A[i], 0);
		if(A[i] < 0)add(i, T, 0, -A[i], 0);
	}
	int flow, cost;
	EK(flow, cost);
	if(flow != tot)puts("-1");
	else
	{
		printf("%d\n", cost);
		for(int i = 0; i < m * 4; i += 4)
		{
			if(!f[i])putchar('R');
			else if(!f[i + 2])putchar('B');
			else putchar('U');
		}
	}
	return 0;
}