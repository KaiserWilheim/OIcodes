#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int maxn[N], maxm[N];
int stre[N];
void dfs(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		stre[p]++;
		int v = maxn[e[i]] + stre[e[i]];
		if(v > maxn[p])maxm[p] = maxn[p], maxn[p] = v;
		else maxm[p] = max(maxm[p], v);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans = max(ans, maxn[i] + maxm[i] + stre[i] + 1 + (i != 1));
	printf("%d\n", ans);
	return 0;
}