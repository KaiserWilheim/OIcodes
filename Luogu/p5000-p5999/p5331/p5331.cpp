#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 3;
const ll INF = 1e16;
int n, m;
int S, T;
ll a[N], b[N], tt;
int px[N], py[N], cnt;
int h[N], e[M], ne[M], idx;
ll w[M], f[M];
void add(int a, int b, ll c, ll d)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = c, w[idx] = d, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, w[idx] = -d, h[b] = idx++;
}
ll d[N];
bool vis[N];
bool spfa()
{
	queue<int>q;
	for(int i = 0; i <= cnt; i++)
		d[i] = INF, vis[i] = false;
	q.push(S), d[S] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = false;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[i] && d[v] > d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				if(!vis[v])
				{
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return d[T] != INF;
}
ll find(int u, ll lim)
{
	if(u == T)return lim;
	ll flow = 0;
	vis[u] = true;
	for(int i = h[u]; ~i && flow < lim; i = ne[i])
	{
		int v = e[i];
		if(d[v] == d[u] + w[i] && f[i] && !vis[v])
		{
			ll t = find(v, min(f[i], lim - flow));
			if(!t)continue;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	vis[u] = false;
	return flow;
}
void dinic(ll &flow, ll &cost)
{
	flow = 0, cost = 0;
	while(spfa())
	{
		ll k;
		while((k = find(S, INF)))
		{
			flow += k;
			cost += k * d[T];
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
	dinic(flow, cost);
	printf("%lld\n", cost);
	return 0;
}
