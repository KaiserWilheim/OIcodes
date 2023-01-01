#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 40;
ll qpow(ll a, ll x, ll mod)
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
ll kpd(ll a, ll b)
{
	return b ? kpd(b, a % b) : a;
}
void exgcd(ll a, ll b, ll &x, ll &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
	}
	else
	{
		exgcd(b, a % b, x, y);
		ll t = x; x = y;
		y = t - a / b * y;
	}
}
ll inv(ll a, ll mod)
{
	ll x, y;
	exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}
ll bsgs(ll a, ll b, ll mod)
{
	map<ll, ll>f;
	ll m = ceil(sqrt(mod));
	b %= mod;
	for(ll i = 1; i <= m; i++)
	{
		b = b * a % mod;
		f[b] = i;
	}
	ll tmp = qpow(a, m, mod);
	b = 1;
	for(ll i = 1; i <= m; i++)
	{
		b = b * tmp % mod;
		if(f[b])return (i * m - f[b] + mod) % mod;
	}
	return -1;
}
ll exbsgs(ll a, ll b, ll mod)
{
	if(b == 1 || mod == 1)return 0;
	ll g = kpd(a, mod), k = 0, n = 1;
	while(g > 1)
	{
		if(b % g != 0)return -1;
		k++;
		b /= g, mod /= g, n = n * (a / g) % mod;
		if(n == b)return k;
		g = kpd(a, mod);
	}
	ll f = bsgs(a, b * inv(n, mod) % mod, mod);
	if(f == -1)return -1;
	return f + k;
}
ll fac(ll n, ll p, ll pk)
{
	if(!n)return 1;
	ll res = 1;
	for(ll i = 2; i <= pk; i++)
		if(i % p)res = res * i % pk;
	res = qpow(res, n / pk, pk);
	for(ll i = 2; i <= n % pk; i++)
		if(i % p)res = res * i % pk;
	return res * fac(n / p, p, pk) % pk;
}
ll CRT(ll b, ll p, ll mod)
{
	return b * inv(p / mod, mod) % p * (p / mod) % p;
}
ll calc(ll n, ll m, ll p, ll pk)
{
	ll up = fac(n, p, pk), d1 = fac(m, p, pk), d2 = fac(n - m, p, pk);
	ll k = 0;
	for(ll i = n; i; i /= p)k += i / p;
	for(ll i = m; i; i /= p)k -= i / p;
	for(ll i = n - m; i; i /= p)k -= i / p;
	return up * inv(d1, pk) % pk * inv(d2, pk) % pk * qpow(p, k, pk) % pk;
}
ll exlucas(ll n, ll m, ll mod)
{
	ll res = 0, tmp = mod, pk;
	int lim = sqrt(mod) + 5;
	for(ll i = 2; i <= lim; i++)
	{
		if(tmp % i == 0)
		{
			pk = 1;
			while(tmp % i == 0)pk *= i, tmp /= i;
			res = (res + CRT(calc(n, m, i, pk), mod, pk)) % mod;
		}
	}
	if(tmp > 1)res = (res + CRT(calc(n, m, tmp, tmp), mod, tmp)) % mod;
	return res;
}
int main()
{
	int n;
	scanf("%d", &n);
	int op;
	ll x, y, z, mod;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%lld%lld%lld", &op, &y, &z, &mod);
		if(op == 1)
		{
			x = qpow(y, z, mod);
			printf("%lld\n", x);
		}
		else if(op == 2)
		{
			x = exbsgs(y, z, mod);
			if(x == -1)puts("Math Error");
			else printf("%lld\n", x);
		}
		else if(op == 3)
		{
			x = exlucas(z, y, mod);
			printf("%lld\n", x);
		}
	}
	return 0;
}