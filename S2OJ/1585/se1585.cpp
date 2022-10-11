#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310;
const ll mod = 998244353;
int n, m;
int a[N];
ll f[N][N][N], g[N][N][N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	g[0][0][0] = 1;
	for(int i = 1; i <= m; i++)
		g[0][0][i] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = 0; k <= m; k++)
			{
				int l = a[i] - a[i - 1] + k;
				l = min(l, m);
				if(l < 0)continue;
				if(k <= j)
				{
					l = g[i - 1][j - k][l];
					f[i][j][k] = (f[i][j][k] + l) % mod;
				}
				if(k)g[i][j][k] = (g[i][j][k - 1] + f[i][j][k]) % mod;
				else g[i][j][k] = f[i][j][k];
			}
		}
	}
	ll res = 0;
	for(int i = 0; i <= m; i++)
		res = (res + f[n][m][i]) % mod;
	printf("%lld\n", res);
	return 0;
}