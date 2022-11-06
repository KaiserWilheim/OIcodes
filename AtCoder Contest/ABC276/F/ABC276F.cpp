#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) ((x)&(-(x)))
const int N = 400010;
const ll mod = 998244353;
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
int a[N];
ll tc[N], ts[N];
void cntadd(int x)
{
	for(int i = x; i <= m; i += lowbit(i))
		tc[i]++;
}
ll cntsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res = (res + tc[i]) % mod;
	return res;
}
void segadd(int x)
{
	for(int i = x; i <= m; i += lowbit(i))
		ts[i] = (ts[i] + x) % mod;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res = (res + ts[i]) % mod;
	return res;
}
ll ans[N], sum[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		m = max(m, a[i]);
		sum[i] = (sum[i - 1] + a[i]) % mod;
	}
	for(int i = 1; i <= n; i++)
	{
		ans[i] = ans[i - 1] + a[i];
		ll les = cntsum(a[i]);
		ll gre = ((sum[i - 1] - segsum(a[i])) % mod + mod) % mod;
		ans[i] = ((ans[i] + les * a[i] % mod * 2ll % mod) % mod + gre * 2ll % mod) % mod;
		cntadd(a[i]);
		segadd(a[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		ll res = ans[i] * qpow(1ll * i * i % mod, mod - 2) % mod;
		printf("%lld\n", res);
	}
	return 0;
}
