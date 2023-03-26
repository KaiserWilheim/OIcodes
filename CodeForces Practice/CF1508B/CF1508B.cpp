#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n, m, K;
ll mod;
ll fac[N], C[N][N];
ll f[N][N][N];
ll add(ll a, ll b)
{
	return a + b >= mod ? a + b - mod : a + b;
}
ll get(int i, int j, int k)
{
	if(!j && (k > i || k < 1))return fac[i];
	return f[i][j][k];
}
int main()
{
	scanf("%d%d%d%lld", &n, &m, &K, &mod);
	fac[0] = 1, C[0][0] = 1;
	f[1][1][1] = 1;
	for(int i = 1; i <= n; i++)
	{
		C[i][0] = 1;
		fac[i] = fac[i - 1] * i % mod;
		for(int j = 1; j <= i; j++)
			C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
	}
	for(int i = 2; i <= n; i++)
	{
		for(int j = 0; j <= min(i, K); j++)
		{
			for(int k = 1; k <= min(i - j + 1, m); k++)
			{
				int g = j - (k == 1);
				f[i][j][k] = get(i - 1, g, k - 1) * 2 % mod;
				for(int p = 2; p < i; p++)
				{
					for(int c = 0; c <= min(p, g); c++)
					{
						ll x = get(p - 1, c, k - 1), y = get(i - p, g - c, k - 1);
						if(x && y)f[i][j][k] = add(f[i][j][k], x * y % mod * C[i - 1][p - 1] % mod);
					}
				}
			}
		}
	}
	printf("%lld\n", f[n][K][m]);
	return 0;
}
