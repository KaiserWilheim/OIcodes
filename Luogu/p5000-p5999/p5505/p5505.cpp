#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1;
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
int a[N];
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
		scanf("%d", &a[i]);
	fac[0] = 1;
	for(int i = 1; i <= 10000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[10000] = qpow(fac[10000]);
	for(int i = 9999; i; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	ll ans = 0;
	for(int i = 0; i < n; i++)
	{
		ll res = C(n, i);
		for(int j = 1; j <= m; j++)
			res = res * C(a[j] + n - i - 1, n - i - 1) % mod;
		if(i & 1)ans = (ans - res + mod) % mod;
		else ans = (ans + res) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
