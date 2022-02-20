#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = 100010, INF = 1e8;
int n, m, S, T;
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

int main()
{
	scanf("%d", &n);
	S = 0, T = n + 1;
	memset(h, -1, sizeof h);
	int tot = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &s[i]);
		tot += s[i];
		add(i, i < n ? i + 1 : 1, INF, 1);
		add(i, i > 1 ? i - 1 : n, INF, 1);
	}
	tot /= n;
	for(int i = 1; i <= n; i++)
		if(tot < s[i])
			add(S, i, s[i] - tot, 0);
		else if(tot > s[i])
			add(i, T, tot - s[i], 0);
	printf("%d\n", EK());
	return 0;
}

