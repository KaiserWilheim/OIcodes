#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 200010;
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
ll C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
signed main()
{
	n = 200000;
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n] = qpow(fac[n], mod - 2);
	for(int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		ll res1 = 0, res2 = 0;
		for(int i = k & 1; i <= min(n, k); i += 2)
			res1 = add(res1, C(n, i));
		for(int i = k & 1; i <= min(m, k); i += 2)
			res2 = add(res2, C(m, i));
		ll ans = res1 * res2 % mod;
		res1 = res2 = 0;
		for(int i = k & 1; i <= min(n, k); i += 2)
			if((n - i - k) % 2 == 0 && n - i <= min(n, k))
				res1 = add(res1, C(n, i));
		for(int i = k & 1; i <= min(m, k); i += 2)
			if((m - i - k) % 2 == 0 && m - i <= min(m, k))
				res2 = add(res2, C(m, i));
		ans = add(ans, mod - res1 * res2 % mod * qpow(2, mod - 2) % mod);
		printf("%lld\n", ans);
	}
	return 0;
}
