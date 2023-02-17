#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = 5010;
int n, K;
int c[N]; ll v[N];
ll f[N][M][N];
signed main()
{
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++)
		scanf("%lld%d", &v[i], &c[i]);
	int V = 2500;
	memset(f, -63, sizeof(f));
	f[0][V][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = c[i] * 2; j <= V * 2 - c[i] * 2; j++)
		{
			for(int k = 0; k <= K; k++)
			{
				f[i][j][k] = f[i - 1][j][k];
				f[i][j][k] = max(f[i][j][k], f[i - 1][j - c[i]][k] + v[i]);
				f[i][j][k] = max(f[i][j][k], f[i - 1][j + c[i]][k] + v[i]);
				if(k)
				{
					f[i][j][k] = max(f[i][j][k], f[i - 1][j - 2 * c[i]][k - 1] + v[i]);
					f[i][j][k] = max(f[i][j][k], f[i - 1][j + 2 * c[i]][k - 1] + v[i]);
				}
			}
		}
	}
	ll ans = 0;
	for(int k = 0; k <= K; k++)
		ans = max(ans, f[n][V][k]);
	printf("%lld\n", ans);
	return 0;
}
