#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 300010, M = N << 1;
int n, m;
int w[N];
bool vis[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll ans[N], cur;
int sz[N];
ll tag[N], num[N], cnt[N];
void dfs1(int p, int fa)
{
	sz[p] = 1;
	int tmp = cnt[w[fa]];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
	}
	cnt[w[p]]++;
	if(fa)
	{
		tag[p] = sz[p] - cnt[w[fa]] + tmp;
		cnt[w[fa]] = sz[p] + tmp;
	}
}
void dfs2(int p, int fa)
{
	int tmp = num[w[fa]];
	cur += tag[p] - num[w[fa]];
	num[w[fa]] = tag[p];
	ans[p] = n * m - cur + num[w[p]];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs2(e[i], p);
	}
	num[w[fa]] = tmp;
	cur -= tag[p] - num[w[fa]];
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
		if(!vis[w[i]])vis[w[i]] = true, m++;
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	for(int i = 0; i <= n; i++)
		if(vis[i])
			cur += n - cnt[i], num[i] = n - cnt[i];
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}