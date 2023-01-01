#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
const ll mod = 1234567891;
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
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll a[N];
ll PRE[N], *pre = PRE + 1;
ll ans;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n + 1; i++)
	{
		scanf("%lld", &a[i]);
		if(a[i] < 0)a[i] = a[i] % mod + mod;
	}
	fac[0] = 1;
	for(int i = 1; i <= n + 2; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n + 2] = qpow(fac[n + 2], mod - 2);
	for(int i = n + 1; i >= 1; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	pre[0] = C(n + 2, 1) - 1;
	ans = a[n + 1] * pre[0] % mod;
	for(int i = 1; i <= n; i++)
	{
		pre[i] = (pre[i - 1] + C(n + 2, n - i + 2) - 1) % mod;
		ans = (ans + a[i] * (C(n + 2, n - i + 2) - 1)) % mod;
	}
	printf("%lld\n", ans);
	int l, r;
	ll p;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%lld", &l, &r, &p);
		if(p < 0)p = p % mod + mod;
		ans = (ans + (pre[r] - pre[l - 1] + mod) * p % mod) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
