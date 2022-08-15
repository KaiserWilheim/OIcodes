#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50;
const ll mod = 1e9 + 7;
ll n, m;
ll ans;
ll a[N];
ll inv[N];
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
ll C(ll n, ll m)
{
	if(n < 0 || m < 0 || n < m)return 0;
	if(n % mod == 0 || m == 0)return 1;
	ll res = 1;
	for(ll i = n - m + 1; i <= n; i++)
		res = (res * (i % mod)) % mod;
	for(int i = 1; i <= m; i++)
		res = (res * inv[i]) % mod;
	return res % mod;
}
int main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= 20; i++)
		inv[i] = qpow(i, mod - 2);
	ans = C(n + m - 1, n - 1);
	for(int i = 1; i <= (1 << n) - 1; i++)
	{
		ll k = n + m, p = 0;
		for(int j = 0; j < n; j++)
		{
			if((1 << j) & i)
			{
				p++;
				k -= a[j + 1];
			}
		}
		k -= p + 1;
		if(p & 1)ans = (ans - C(k, n - 1) + mod) % mod;
		else ans = (ans + C(k, n - 1)) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
