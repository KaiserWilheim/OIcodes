#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int k;
int h[N], e[M], ne[M], idx;
int c[N], w[M];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll sum[N], dis[N];
ll ans[N];
void dfs1(int p, int fa)
{
	sum[p] = c[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sum[p] += sum[e[i]];
		dis[p] += dis[e[i]] + sum[e[i]] * w[i];
	}
}
void dfs2(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		ans[e[i]] = ans[p] + (k - 2 * sum[e[i]]) * w[i];
		dfs2(e[i], p);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
		k += c[i];
	}
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dfs1(1, 0);
	ans[1] = dis[1];
	dfs2(1, 0);
	ll res = INT64_MAX;
	for(int i = 1; i <= n; i++)
		res = min(res, ans[i]);
	printf("%lld\n", res);
	return 0;
}