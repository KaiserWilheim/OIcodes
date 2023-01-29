#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 3;
const int INF = 1e9;
int n, m;
int S, T;
ll a[N], b[N], tt;
int px[N], py[N], cnt;
int h[N], e[M], ne[M], idx;
ll w[M], f[M];
void add(int a, int b, int c, int d)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = c, w[idx] = d, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, w[idx] = -d, h[b] = idx++;
}
ll d[N], pre[N], incf[N];
bool st[N];
bool spfa()
{
	queue<int>q;
	memset(d, 63, sizeof(d));
	memset(incf, 0, sizeof(incf));
	q.push(S), d[S] = 0, incf[S] = INF;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		st[u] = false;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[i] && d[v] > d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				pre[v] = i;
				incf[v] = min(f[i], incf[u]);
				if(!st[v])
				{
					q.push(v);
					st[v] = true;
				}
			}
		}
	}
	return incf[T] > 0;
}
void EK(ll &flow, ll &cost)
{
	flow = cost = 0;
	while(spfa())
	{
		ll t = incf[T];
		flow += t, cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
void solve(int l, int r)
{
	if(l >= r)return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	tt = 0;
	for(int i = l; i <= r; i++)
		b[++tt] = a[i];
	sort(b + 1, b + 1 + tt);
	tt = unique(b + 1, b + 1 + tt) - b - 1;
	for(int i = 1; i < tt; i++)
	{
		add(cnt + i, cnt + i + 1, INF, b[i + 1] - b[i]);
		add(cnt + i + 1, cnt + i, INF, b[i + 1] - b[i]);
	}
	for(int i = l; i <= r; i++)
	{
		int pos = lower_bound(b + 1, b + 1 + tt, a[i]) - b;
		if(i > mid)add(px[i], cnt + pos, 1, 0);
		else add(cnt + pos, py[i], 1, 0);
	}
	cnt += tt;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	int W;
	scanf("%d", &W);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	S = 0, T = ++cnt;
	for(int i = 1; i <= n; i++)
	{
		px[i] = ++cnt, py[i] = ++cnt;
		add(S, px[i], 1, 0), add(px[i], T, 1, W), add(py[i], T, 1, 0);
	}
	solve(1, n);
	ll flow, cost;
	EK(flow, cost);
	printf("%lld\n", cost);
	return 0;
} 
