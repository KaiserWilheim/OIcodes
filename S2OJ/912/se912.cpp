#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 998244353;
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
int n, m;
ll a[N];
ll sum = 0;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum = (sum + a[i]) % mod;
	}
	ll ans = a[1] * qpow(a[1], mod - 2) % mod;
	for(int i = 2; i <= n; i++)
		ans = (ans + a[1] * qpow(a[1] + a[i] % mod, mod - 2) % mod) % mod;
	ans = (mod - ans + n + 1) % mod;
	printf("%lld\n", ans);
	return 0;
}