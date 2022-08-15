#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
const ll mod = 1e9 + 9;
int n, k;
int a[N], b[N];
int t[N];
ll f[N][N];
ll fac[N], inv[N];
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
inline ll C(ll x, ll y)
{
	if(x < y)return 0;
	return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)scanf("%d", &b[i]);
	if(n < k || (n + k) & 1)
	{
		puts("0");
		return 0;
	}
	k = (n + k) / 2;
	fac[0] = 1;
	for(int i = 1; i <= 2000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[2000] = qpow(fac[2000], mod - 2);
	for(int i = 1999; i >= 1; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	for(int i = 1, j = 1; i <= n; i++)
	{
		while(j <= n && b[j] < a[i])j++;
		t[i] = j - 1;
	}
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			if(j == 0)f[i][j] = 1;
			else f[i][j] = (f[i - 1][j] + 1ll * max(0, t[i] - j + 1) * f[i - 1][j - 1] % mod) % mod;
		}
	}
	ll ans = 0;
	for(int i = k; i <= n; i++)
	{
		ll w = ((i - k) & 1) ? -1ll : 1ll;
		ll res = (C(i, k) * fac[n - i]) % mod;
		res = (res * f[n][i]) % mod;
		ans = (ans + res * w + mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
