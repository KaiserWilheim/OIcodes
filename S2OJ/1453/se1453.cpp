#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 998244353;
ll fac[100010], inv[100010];
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res % mod;
}
ll f(int n, int m)
{
	if(m == n)
	{
		return 1ll;
	}
	else if(m == n - 1)
	{
		ll res = (2 * n) % mod;
		return res;
	}
	else if(m == 0)
	{
		return qpow(2, n);
	}
	else
	{
		ll res = (fac[n] * inv[m + 1]) % mod * inv[n - m] % mod;
		res = (res * qpow(2, n - m - 1)) % mod;
		res = (res * f(m + 1, m)) % mod;
		return res;
	}
}
int main()
{
	fac[0] = 1;
	for(ll i = 1; i <= 100000; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
	}
	inv[0] = 1; inv[100000] = qpow(fac[100000], mod - 2);
	for(int i = 99999; i >= 1; i--)
	{
		inv[i] = 1 * inv[i + 1] * (i + 1) % mod;
	}
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%lld\n", f(n, m));
	}
	return 0;
}