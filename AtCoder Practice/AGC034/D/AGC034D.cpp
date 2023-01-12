#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 3;
const int INF = 1e9;
int n, m;
int S, T;
int h[N], e[M], ne[M], idx;
ll f[M], w[M];
void add(int a, int b, ll c, ll d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}
ll d[N], pre[N], incf[N];
bool st[N];
bool spfa()
{
	queue<int>q;
	memset(d, 63, sizeof(d));
	memset(incf, 0, sizeof(incf));
	d[S] = 0, incf[S] = INF;
	q.push(S);
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

int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	S = 0, T = n * 2 + 5;
	for(int i = 1; i <= n; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		add(S, i, z, 0);
		add(i, 2 * n + 1, z, x + y);
		add(i, 2 * n + 2, z, x - y);
		add(i, 2 * n + 3, z, -x + y);
		add(i, 2 * n + 4, z, -x - y);
	}
	for(int i = 1; i <= n; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		add(i + n, T, z, 0);
		add(2 * n + 4, i + n, z, x + y);
		add(2 * n + 3, i + n, z, x - y);
		add(2 * n + 2, i + n, z, -x + y);
		add(2 * n + 1, i + n, z, -x - y);
	}
	ll flow, cost;
	EK(flow, cost);
	printf("%lld\n", -cost);
	return 0;
}
