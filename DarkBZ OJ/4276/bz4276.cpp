#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2000010, M = 2000010, INF = 1e8;
int n, m, S, T;
int a[N], b[N], c[N];
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

struct SegTree
{
	int l, r;
	int id;
}tr[N << 3];
int cnt;

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].id = ++cnt;
	if(l == r)
	{
		add(tr[p].id, T, 1, 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	add(tr[p].id, tr[p << 1].id, INF, 0);
	add(tr[p].id, tr[p << 1 | 1].id, INF, 0);
	return;
}
void seglnk(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		add(k + 1, tr[p].id, 1, -c[k]);
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)seglnk(p << 1, l, r, k);
	if(r > mid)seglnk(p << 1 | 1, l, r, k);
	return;
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
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	S = 0, T = 1;
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		add(S, i + 1, 1, 0);
		maxn = max(maxn, b[i]);
	}
	cnt = n + 1;
	build(1, 1, maxn + 1);
	for(int i = 1; i <= n; i++)
		seglnk(1, a[i], b[i] - 1, i);
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", -cost);
	return 0;
}
