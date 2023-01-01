#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1, K = 1 << 8;
int n, m, k;
int f[K][N];
int g[K], ans[K];
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int vis[N];
priority_queue<pair<int, int>>q;
void spfa(int S)
{
	for(int i = 1; i <= n; i++)
		q.emplace(-f[S][i], i);
	memset(vis, 0, sizeof(vis));
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[S][v] > f[S][u] + w[i])
			{
				f[S][v] = f[S][u] + w[i];
				q.emplace(-f[S][v], v);
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	memset(f, 63, sizeof(f));
	memset(g, 63, sizeof(g));
	memset(ans, 63, sizeof(ans));
	for(int i = 1; i <= k; i++)
		f[1 << (i - 1)][i] = 0;
	for(int i = n; i >= n - k + 1; i--)
		f[1 << ((n - i + 1) + k - 1)][i] = 0;
	for(int S = 0; S < (1 << 2 * k); S++)
	{
		for(int i = 1; i <= n; i++)
			for(int T = S; T; T = S & (T - 1))
				f[S][i] = min(f[S][i], f[S ^ T][i] + f[T][i]);
		spfa(S);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int S = 0; S < (1 << 2 * k); S++)
		{
			int T = 0;
			for(int j = 1; j <= k; j++)
				if((S >> (j - 1) & 1) && (S >> (j + k - 1) & 1))
					T |= (1 << (j - 1));
			g[T] = min(g[T], f[S][i]);
		}
	}
	ans[0] = 0;
	for(int S = 0; S < (1 << k); S++)
		for(int T = S; T; T = (T - 1) & S)
			ans[S] = min(ans[S], ans[S ^ T] + g[T]);
	if(ans[(1 << k) - 1] >= 10000000)
	{
		puts("-1");
		return 0;
	}
	printf("%d\n", ans[(1 << k) - 1]);
	return 0;
}