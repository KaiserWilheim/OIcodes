#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5010, M = 100010, INF = 1e8;
int n, m, S, T;
int p, x, xp, y, yp;
int need[N];
int s[N];
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a]; h[a] = idx++;
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

int EK()
{
	int cost = 0;
	while(spfa())
	{
		int t = incf[T];
		cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
	return cost;
}

signed main()
{
	scanf("%lld", &n);
	scanf("%lld%lld%lld%lld%lld", &p, &x, &xp, &y, &yp);
	S = 0, T = n * 2 + 1;
	memset(h, -1, sizeof h);
	for(int i = 1; i <= n; i++)scanf("%lld", &need[i]);
	for(int i = 1; i <= n; i++)
	{
		int r = need[i];
		add(S, i, r, 0);
		add(n + i, T, r, 0);
		add(S, n + i, INF, p);
		if(i < n) add(i, i + 1, INF, 0);
		if(i + x <= n) add(i, n + i + x, INF, xp);
		if(i + y <= n) add(i, n + i + y, INF, yp);
	}
	printf("%lld\n", EK());
	return 0;
}
