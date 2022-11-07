#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
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
int n, m, k;
ll fac[N], inv[N];
void init()
{
	fac[0] = 1;
	for(int i = 1; i <= 200000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[200000] = qpow(fac[200000], mod - 2);
	for(int i = 199999; i; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}
ll y[N], prf[N], suf[N];
ll f(int n, int x)
{
	if(x <= n)return y[x];
	prf[0] = suf[n + 1] = 1;
	for(int i = 1; i <= n; i++)prf[i] = prf[i - 1] * (x - i) % mod;
	for(int i = n; i >= 1; i--)suf[i] = suf[i + 1] * (x - i) % mod;
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		ll tmp = y[i] * prf[i - 1] % mod * inv[i - 1] % mod * suf[i + 1] % mod * inv[n - i] % mod;
		res = (res + ((n - i) & 1 ? (mod - 1) : 1) * tmp % mod) % mod;
	}
	return res;
}
void solve()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n + m + 2; i++)
		y[i] = (y[i - 1] + qpow(i, n + m) - qpow(i - 1, n) * qpow(i, m) % mod + mod - qpow(i, n) * qpow(i - 1, m) % mod + qpow(i - 1, n + m) + mod) % mod;
	printf("%lld\n", f(n + m + 2, k));
}
int main()
{
	int T;
	scanf("%d", &T);
	init();
	while(T--)
	{
		solve();
	}
	return 0;
}