#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = N << 1;
int n, m, K;
ll a[N][N];
ll f[N][N];
ll prf[N][N], suf[N][N];
int main()
{
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	memset(f, 63, sizeof(f));
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(i == j)continue;
			f[i][j] = a[1][i] + a[1][j];
		}
	}
	for(int k = 2; k <= n; k++)
	{
		memset(prf, 63, sizeof(prf));
		memset(suf, 63, sizeof(suf));
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= m; j++)
				prf[i][j] = min(prf[i - 1][j], f[i][j] - K * i);
		for(int i = m; i; i--)
			for(int j = 1; j <= m; j++)
				suf[i][j] = min(suf[i + 1][j], f[i][j] + K * i);
		memset(f, 63, sizeof(f));
		for(int i = 1; i <= m; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				f[i][j] = min(prf[i][j] + K * i + a[k][i], suf[i][j] - K * i + a[k][i]);
			}
		}
		memset(prf, 63, sizeof(prf));
		memset(suf, 63, sizeof(suf));
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= m; j++)
				prf[i][j] = min(prf[i][j - 1], f[i][j] - K * j);
		for(int i = 1; i <= m; i++)
			for(int j = m; j; j--)
				suf[i][j] = min(suf[i][j + 1], f[i][j] + K * j);
		memset(f, 63, sizeof(f));
		for(int i = 1; i <= m; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				if(i == j)continue;
				f[i][j] = min(prf[i][j] + K * j + a[k][j], suf[i][j] - K * j + a[k][j]);
			}
		}
	}
	ll ans = 1e15;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			ans = min(ans, f[i][j]);
	printf("%lld\n", ans);
	return 0;
}