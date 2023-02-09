#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010, M = N << 1;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n, d;
int r[N];
ll fac[N], inv[N];
ll f[45][45][2500];
ll C(int n, int m)
{
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
	scanf("%d%d", &n, &d);
	fac[0] = 1;
	for(int i = 1; i <= d; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[d] = qpow(fac[d], mod - 2);
	for(int i = d; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	for(int i = 1; i <= n; i++)
		scanf("%d", &r[i]);
	sort(r + 1, r + 1 + n);
	f[0][0][0] = 1;
	int m = r[n];
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			for(int k = 0; k <= m * (i - j + 2); k++)
			{
				int t = r[i + 1];
				if(j >= 1)f[i + 1][j][k + t] = add(f[i + 1][j][k + t], f[i][j][k] * 2 * j % mod);
				if(j >= 2 && k)f[i + 1][j - 1][k + t * 2 - 1] = add(f[i + 1][j - 1][k + t * 2 - 1], f[i][j][k] * j * (j - 1) % mod);
				f[i + 1][j + 1][k + 1] = add(f[i + 1][j + 1][k + 1], f[i][j][k]);
			}
		}
	}
	ll ans = 0;
	for(int i = 0; i <= n * m; i++)
		ans = add(ans, C(d - i + n, n) * f[n][1][i] % mod);
	printf("%lld\n", ans);
	return 0;
}
