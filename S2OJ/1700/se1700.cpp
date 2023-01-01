#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 60, M = 200;
const ll mod = 998244353;
int n, m, K;
ll f[N][M][N], sum[N][M][N];
ll calc(int n, int m, int K)
{
	ll res = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= K; k++)
				res = (res + f[i][j][k]) % mod;
	return res;
}
int main()
{
	scanf("%d%d%d", &n, &m, &K);
	f[0][0][0] = 1;
	for(int k = 0; k <= K; k++)
		sum[0][0][k] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			for(int k = 1; k <= K; k++)
			{
				sum[i][j][k] = sum[i][j][k - 1];
				if(j < i || i < k || j < (k * (k + 1) / 2) || (1ll << i) < k)continue;
				for(int x = 0; x < i; x++)
				{
					for(int y = 0; y <= j - k; y++)
					{
						f[i][j][k] += f[x][y][k - 1] * sum[i - 1 - x][j - k - y][k - 1];
						if(k >= 2)f[i][j][k] += f[i - 1 - x][j - k - y][k - 1] * sum[x][y][k - 2];
						f[i][j][k] %= mod;
					}
				}
				sum[i][j][k] = (sum[i][j][k] + f[i][j][k]) % mod;
			}
		}
	}
	ll res = 0;
	for(int i = 1; i <= K && i < m; i++)
		res = (res + calc(n - 1, m - i, i - 1)) % mod;
	printf("%lld\n", res);
	return 0;
}