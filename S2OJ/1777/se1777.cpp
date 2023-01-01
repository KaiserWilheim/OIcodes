#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310;
const ll mod = 1e9 + 7;
int n;
ll p[N];
ll pw[N][N], f[N][N];
ll ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
		scanf("%lld", &p[i]);
	for(int i = 1; i < n; i++)
	{
		pw[i][0] = 1;
		for(int j = 1; j <= n; j++)
			pw[i][j] = pw[i][j - 1] * (1 - p[i] + mod) % mod;
	}
	for(int m = 1; m <= n; m++)
	{
		memset(f, 0, sizeof(f));
		f[1][m] = 1;
		for(int i = 1; i < n; i++)
		{
			for(int j = 1; j <= n - i + 1; j++)
			{
				if(j < n - i + 1)f[i + 1][j] = (f[i + 1][j] + f[i][j] * pw[i][j] % mod) % mod;
				if(j >= 2)f[i + 1][j - 1] = (f[i + 1][j - 1] + f[i][j] * (1 - pw[i][j - 1] + mod) % mod) % mod;
			}
		}
		ans = (ans + m * f[n][1] % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}