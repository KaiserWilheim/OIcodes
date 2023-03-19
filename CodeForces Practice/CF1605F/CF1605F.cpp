#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
ll mod;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
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
ll calc(ll n, ll m)
{
	ll res = 1;
	for(ll i = n; i >= n - m + 1; i--)
		res = res * i % mod;
	return res;
}
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int n, m;
ll f[N][N], g[N][N], h[N][N];
ll ne(int n) { return (n & 1) ? (mod - 1) : 1; }
int main()
{
	scanf("%d%d%lld", &n, &m, &mod);
	fac[0] = 1;
	for(int i = 1; i <= 100; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[100] = qpow(fac[100], mod - 2);
	for(int i = 100; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = 0; k <= j; k++)
			{
				f[i][j] = add(f[i][j], C(j, k) * ne(j - k) % mod * qpow(2, i * k) % mod);
				h[i][j] = add(h[i][j], C(j, k) * ne(j - k) % mod * calc(qpow(2, k) - 1, i) % mod);
			}
		}
	}
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int x = 0; x < i; x++)
			{
				for(int y = 0; y < j; y++)
				{
					if((n & 1) && (i == n) && (x == n - 1))continue;
					g[i][j] = add(g[i][j], C(i, x) * C(j, y) % mod * qpow(2, y * (i - x)) % mod * h[i - x][j - y] % mod * add(f[x][y], mod - g[x][y]) % mod);
				}
			}
		}
	}
	ll ans = 0;
	for(int i = 0; i <= m; i++)
		ans = add(ans, C(m, i) * add(f[n][i], mod - g[n][i]) % mod);
	printf("%lld\n", ans);
	return 0;
}
