#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000, M = 150000;
int n, m;
int c[N], w[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int sum[N], ans;
bool vis[N];
void dfs(int p)
{
	sum[c[p]] += w[p];
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
		if(!vis[e[i]])dfs(e[i]);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++)scanf("%d", &w[i]);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	for(int i = 1; i <= n; i++)
	{
		if(c[i] != 1)continue;
		memset(sum, 0, sizeof(sum));
		memset(vis, 0, sizeof(vis));
		dfs(i);
		for(int j = 2; j <= n; j++)
			ans = max(ans, sum[j] / sum[1]);
	}
	printf("%d\n", ans);
	return 0;
}
