#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
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
ll sub(ll a, ll b)
{
	return a < b ? a - b + mod : a - b;
}
int n;
ll k;
ll x[N], y[N];
ll lagrange()
{
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		ll l = 1;
		for(int j = 1; j <= n; j++)
		{
			if(i == j)continue;
			l = l * sub(k, x[j]) % mod * qpow(sub(x[i], x[j])) % mod;
		}
		res = (res + l * y[i]) % mod;
	}
	return res;
}
int main()
{
	scanf("%d%lld", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &x[i], &y[i]);
	printf("%lld\n", lagrange());
	return 0;
}
