#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 200010;
ll n, m, mod;
ll fac[N];
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
ll C(ll n, ll m)
{
	if(m > n)return 0;
	return fac[n] * qpow(fac[m], mod - 2) % mod * qpow(fac[n - m], mod - 2) % mod;
}
ll lucas(ll n, ll m)
{
	if(!m)return 1ll;
	return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld%lld", &n, &m, &mod);
		fac[0] = 1;
		for(int i = 1; i <= mod; i++)
			fac[i] = fac[i - 1] * i % mod;
		printf("%lld\n", lucas(n + m, n));
	}
	return 0;
}
