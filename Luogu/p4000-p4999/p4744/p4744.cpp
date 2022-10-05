#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = 60;
const int INF = 1e9;
int n, m, k;
int a[N];
int f[N][M], g[N][M];
int ans = -INF;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] += a[i - 1];
	}
	memset(f, 0xc1, sizeof(f));
	memset(g, 0xc1, sizeof(g));
	f[0][0] = 0;
	for(int j = 0; j <= k; j++)
	{
		int maxn = -INF;
		for(int i = 1; i <= n; i++)
		{
			if(j)f[i][j] = max(f[i][j], maxn + a[i]);
			f[i][j] = max(f[i][j], f[i - 1][j]);
			maxn = max(maxn, f[i][j - 1] - a[i]);
		}
	}
	ans = f[n][k];
	for(int i = 1; i <= n; i++)
		g[i][1] = max(a[i], g[i - 1][1]);
	for(int j = 2; j <= k; j++)
	{
		int maxn = -INF;
		for(int i = 1; i <= n; i++)
		{
			g[i][j] = max(g[i][j], max(maxn + a[i], g[i - 1][j]));
			maxn = max(maxn, g[i][j - 1] - a[i]);
		}
	}
	for(int i = 1; i <= n; i++)
		ans = max(ans, g[i][k] + a[n] - a[i]);
	printf("%d\n", ans);
	return 0;
}