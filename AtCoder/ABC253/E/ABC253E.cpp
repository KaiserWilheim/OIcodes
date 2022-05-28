#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
const ll p = 998244353;
ll sum[N][N], dp[N][N];
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;
	}
	return res;
}
int main()
{
	int n, m, c;
	scanf("%d%d%d", &n, &m, &c);
	if(c == 0)
	{
		ll ans = qpow(m, n);
		printf("%lld\n", ans);
		return 0;
	}
	for(int i = 1; i <= m; i++)
	{
		dp[1][i] = 1, sum[1][i] = i;
	}
	for(int i = 2; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			dp[i][j] = ((sum[i - 1][m] - sum[i - 1][min(m, j + c - 1)] + sum[i - 1][max(0, j - c)]) % p + p) % p;
			sum[i][j] = (sum[i][j - 1] + dp[i][j]) % p;
		}
	}
	printf("%lld\n", sum[n][m]);
	return 0;
}
