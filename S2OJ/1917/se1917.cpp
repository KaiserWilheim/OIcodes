#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310, M = 100010;
const ll mod = 1e9 + 7;
const ll inv2 = 5e8 + 4, inv6 = 166666668;
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
ll C2(ll n) { return n % mod * ((n + 1) % mod) % mod * inv2 % mod; }
ll C6(ll n)
{
	n %= mod;
	return n * (n + 1) % mod * (n + n + 1) % mod * inv6 % mod;
}
ll calc2(ll l, ll r) { return (C2(r) - C2(l - 1) + mod) % mod; }
ll calc3(ll l, ll r)
{
	while(l % 3 != 0)l++;
	while(r % 3 != 0)r--;
	return r / 3 - l / 3 + 1;
}
ll calc6(ll l, ll r) { return (C6(r) - C6(l - 1) + mod) % mod; }
ll calcceil(ll l, ll r)
{
	ll res = 0, a, b;
	a = (l & 1) ? l : l + 1, b = (r & 1) ? r : r - 1;
	if(a <= b)res = (res + calc2((a - 1) / 2, (b - 1) / 2)) % mod;
	a = (l & 1) ? l + 1 : l, b = (r & 1) ? r - 1 : r;
	if(a <= b)res = (res + calc2((a - 1) / 2, (b - 1) / 2)) % mod;
	return res;
}
ll n;
int m, k;
int main()
{
	scanf("%lld%d%d", &n, &m, &k);
	if(m == 1)
	{
		printf("%lld\n", n % mod);
	}
	else if(m == 2)
	{
		if(k == 1)
		{
			ll res = 0;
			for(ll l = 1, r; l <= n; l = r + 1)
			{
				r = n / (n / l);
				res = (res + (n / l) % mod * ((r - l + 1) % mod) % mod) % mod;
			}
			res = (res - n % mod + mod) % mod;
			printf("%lld\n", res);
		}
		else if(k == 2)
		{
			ll res = n % mod * ((n - 1) % mod) % mod * inv2 % mod;
			printf("%lld\n", res);
		}
	}
	else if(m == 3)
	{
		if(k == 1)
		{
			ll res = n / 3 % mod;
			printf("%lld\n", res);
		}
		else if(k == 2)
		{
			ll res = 0;
			for(ll l = 1, r; l <= n; l = r + 1)
			{
				r = n / (n / l);
				res = (res + (n / l) % mod * calcceil(l, r) % mod) % mod;
			}
			printf("%lld\n", res);
		}
		else if(k == 3)
		{
			ll res = n % mod * ((n - 1) % mod) % mod * ((n - 2) % mod) % mod * inv6 % mod;
			printf("%lld\n", res);
		}
	}
	else if(m == 4)
	{
		if(k == 1)
		{
			ll res = 1;
			if(n >= 6)res = (n / 6) % mod + (n / 9) % mod + (n / 10) % mod + (n / 12) % mod + (n / 15) % mod + (n / 21) % mod;
			printf("%lld\n", res % mod);
		}
		else if(k == 2)
		{
			ll res = 1;
			if(n == 7)res = 3;
			else if(n == 8)res = 6;
			else if(n == 9)res = 9;
			else if(n == 10)res = 10;
			else if(n >= 11)res = (n / 11) % mod + (n / 29) % mod;
			printf("%lld\n", res % mod);
		}
		else if(k == 3)
		{
			ll res = 0;
			if(n <= 4)res = 1;
			else if(n == 5)res = 5;
			else
			{
				for(ll l = 1, r; l <= n; l = r + 1)
				{
					r = n / (n / l);
					ll s = 0;
					s = (s + (calc6(l, r) - 3ll * calc2(l, r) % mod + 2ll * (r - l + 1) % mod + mod) % mod * inv2 % mod) % mod;
					s = (s + 2ll * calc3(l, r) % mod) % mod;
					s = (s - 3ll * calcceil(l, r) % mod + mod) % mod;
					res = (res + s * ((n / l) % mod) % mod) % mod;
				}
				res = res * inv6 % mod;
			}
			printf("%lld\n", res);
		}
		else if(k == 4)
		{
			ll res = n % mod * ((n - 1) % mod) % mod * ((n - 2) % mod) % mod * ((n - 3) % mod) % mod;
			res = res * qpow(24, mod - 2) % mod;
			printf("%lld\n", res);
		}
	}
	return 0;
}
