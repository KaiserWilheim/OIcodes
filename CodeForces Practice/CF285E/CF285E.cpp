#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = 400010;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x = mod - 2)
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
int n, m;
ll f[N][N][2][2];
ll F[N];
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(m > n || m < 0)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll add(ll a, ll b)
{
	return (a + b > mod) ? (a + b - mod) : (a + b);
}
int main()
{
	scanf("%d%d", &n, &m);
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n]);
	inv[0] = 1;
	for(int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	f[1][0][0][0] = f[1][1][0][1] = 1;
	for(int i = 2; i < n; i++)
	{
		f[i][0][0][0] = 1;
		for(int j = 1; j <= i; j++)
		{
			f[i][j][0][0] = add(add(f[i - 1][j - 1][0][0], f[i - 1][j][0][0]), f[i - 1][j][1][0]);
			f[i][j][1][0] = add(add(f[i - 1][j - 1][0][1], f[i - 1][j][0][1]), f[i - 1][j][1][1]);
			f[i][j][0][1] = add(f[i - 1][j - 1][0][0], f[i - 1][j - 1][1][0]);
			f[i][j][1][1] = add(f[i - 1][j - 1][0][1], f[i - 1][j - 1][1][1]);
		}
	}
	f[n][0][0][0] = 1;
	for(int j = 1; j <= n; j++)
	{
		f[n][j][0][0] = add(add(f[n - 1][j - 1][0][0], f[n - 1][j][0][0]), f[n - 1][j][1][0]);
		f[n][j][1][0] = add(add(f[n - 1][j - 1][0][1], f[n - 1][j][0][1]), f[n - 1][j][1][1]);
	}
	for(int i = 0; i <= n; i++)
		F[i] = add(f[n][i][0][0], f[n][i][1][0]) * fac[n - i] % mod;
	ll ans = 0;
	for(int i = m; i <= n; i++)
	{
		ll sav = C(i, m) * F[i] % mod;
		ans = add(ans, (i - m) & 1 ? mod - sav : sav);
	}
	printf("%lld\n", ans % mod);
	return 0;
}
