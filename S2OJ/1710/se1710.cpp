#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
const ll mod = 1e9 + 7;
int n, m;
bool st[N];
ll f[N][N], g[N][N];
ll mul[N];
int main()
{
	scanf("%d", &n);
	string s;
	cin >> s;
	for(int i = 0; i < n; i++)
		st[i + 1] = (s[i] == 'L');
	if(n == 1)
	{
		puts("1");
		return 0;
	}
	f[0][0] = 1;
	mul[0] = 1;
	for(int i = 1; i <= n + 5; i++)
		mul[i] = mul[i - 1] * i % mod;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			if(st[i])
				f[i][j] = (f[i][j] + f[i - 1][j] * j % mod + f[i - 1][j + 1] * j % mod * (j + 1) % mod) % mod;
			else
				f[i][j] = (f[i][j] + f[i - 1][j] * j % mod + f[i - 1][j - 1]) % mod;
		}
	}
	g[n + 1][0] = 1;
	for(int i = n; i >= 1; i--)
	{
		for(int j = 1; j <= n - i + 1; j++)
		{
			if(st[i])
				g[i][j] = (g[i][j] + g[i + 1][j] * j % mod + g[i + 1][j - 1]) % mod;
			else
				g[i][j] = (g[i][j] + g[i + 1][j] * j % mod + g[i + 1][j + 1] * j % mod * (j + 1) % mod) % mod;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		ll ans = 0;
		for(int j = 0; j <= i; j++)
		{
			ans = (ans + f[i - 1][j] * g[i + 1][j] * 2 % mod * mul[j] % mod * mul[j] % mod) % mod;
			if(j)ans = (ans + f[i - 1][j] * g[i + 1][j - 1] % mod * mul[j] % mod * mul[j - 1]) % mod;
			ans = (ans + f[i - 1][j] * g[i + 1][j + 1] % mod * mul[j] % mod * mul[j + 1]) % mod;
		}
		printf("%lld ", ans);
	}
	puts("");
	return 0;
}