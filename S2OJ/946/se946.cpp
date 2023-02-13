#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = N << 1;
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
int n, m;
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(m == 0)return 1;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll f[N][N], g[N], h[N], t[N];
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int main()
{
	fac[0] = 1;
	for(int i = 1; i <= 100; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[100] = qpow(fac[100], mod - 2);
	for(int i = 100; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	n = m = 100;
	h[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
			g[i] = add(g[i], C(i - 1, j - 1) * t[j] % mod * h[i - j] % mod);
		h[i] = qpow(2, i * (i - 1) / 2);
		t[i] = (h[i] - g[i] + mod) % mod;
	}
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			f[0][i] = add(f[0][i], C(i - 1, j - 1) * f[0][i - j] % mod);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= n - i; j++)
			for(int p = 1; p <= i; p++)
				for(int q = 0; q <= j; q++)
					f[i][j] = add(f[i][j], C(i - 1, p - 1) * C(j, q) % mod * qpow(qpow(2, p) - 1, q) % mod * h[q] % mod * t[p] % mod * f[i - p][j - q] % mod);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		printf("%lld\n", f[n - m][m]);
	}
	return 0;
}
