#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define ll long long
const int N = 1000010;
const ll mod = 1000000007;
using namespace std;
ll qpow(ll a, ll t)
{
	ll ans = 1;
	while(t)
	{
		if(t & 1)ans = ans * a % mod;
		a = a * a % mod; t >>= 1;
	}
	return ans;
}
ll n, m, ans, y[N], lf[N], rf[N], ifac[N];
int main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m + 2; i++)
		y[i] = (y[i - 1] + qpow(i, m)) % mod;
	m += 2;
	ifac[0] = ifac[1] = 1;
	for(int i = 2; i <= m; i++)
		ifac[i] = ifac[mod % i] * (mod - mod / i) % mod;
	for(int i = 2; i <= m; i++)
		ifac[i] = ifac[i] * ifac[i - 1] % mod;
	lf[0] = 1;
	for(int i = 1; i <= m; i++)
		lf[i] = lf[i - 1] * (n - i) % mod;
	rf[m + 1] = 1;
	for(int i = m; i; i--)
		rf[i] = rf[i + 1] * (n - i) % mod;
	for(int i = 1; i <= m; i++)
		ans = (ans + y[i] * lf[i - 1] % mod *
			   rf[i + 1] % mod * ifac[i - 1] % mod *((m - i) & 1 ? mod - ifac[m - i] : ifac[m - i])) % mod;
	printf("%lld", (ans + mod) % mod);
	return 0;
}
