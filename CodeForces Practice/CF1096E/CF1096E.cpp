#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 400010;
const ll mod = 998244353;
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
int n, r, s;
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(m > n || m < 0)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll F(int n, int m)
{
	if(m < 0)return 0;
	return C(n + m - 1, n - 1);
}
ll add(ll a, ll b)
{
	return (a + b > mod) ? (a + b - mod) : (a + b);
}
ll G(int n, int m, int r)
{
	if(n == 0 && m == 0)return 1;
	ll res = 0, sgn = (n & 1) ? -1 : 1;
	for(int i = 0; i <= n; i++, sgn *= -1)
		if(m - (r + 1) * (n - i) >= 0)
			res = add(res, (sgn * C(n, i) % mod * F(n, m - (r + 1) * (n - i)) % mod + mod) % mod);
	return res;
}
int main()
{
	scanf("%d%d%d", &n, &s, &r);
	fac[0] = 1;
	for(int i = 1; i <= 10000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[10000] = qpow(fac[10000]);
	inv[0] = 1;
	for(int i = 10000; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	ll res = 0;
	for(int i = r; i <= s; i++)
	{
		for(int j = 0; (j + 1) * i <= s && j + 1 <= n; j++)
		{
			int m = n - j - 1, q = s - (j + 1) * i;
			res = add(res, G(m, q, i - 1) * C(n - 1, j) % mod * qpow(j + 1) % mod);
		}
	}
	printf("%lld\n", res * qpow(C(s - r + n - 1, n - 1)) % mod);
	return 0;
}
