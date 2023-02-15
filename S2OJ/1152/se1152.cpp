#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 35;
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
int n, a, b;
bool rev;
int x[N];
ll fac[N], inv[N];
ll C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int cnta, cntb, cntc, cntd;
ll resa, resb, resc, resd;
int main()
{
	n = 100000;
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n] = qpow(fac[n], mod - 2);
	for(int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	scanf("%d%d%d", &n, &a, &b);
	if(a > b)rev = true, swap(a, b);
	for(int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
	if(a == b)
	{
		int odd = 0, even = 0;
		for(int i = 1; i <= n; i++)
		{
			int k = x[i] / a;
			if(k & 1)odd++;
			else even++;
		}
		ll dual = 0;
		for(int i = 0; i <= odd; i += 2)dual = add(dual, C(odd, i));
		resd = qpow(2, even) * dual % mod;
		resc = add(qpow(2, n), mod - resd);
		printf("%lld %lld %lld %lld\n", resa, resb, resc, resd);
		return 0;
	}
	int oui = 0, non = 0;
	for(int i = 1; i <= n; i++)
	{
		x[i] %= a + b;
		if(x[i] >= b)
		{
			cntb++;
			if(x[i] >= a * 2)oui++;
			else non++;
		}
		else if(x[i] >= a)cntc++;
		else cntd++;
	}
	ll dual = 0, homo = 0;
	for(int i = 0; i <= non; i += 2)dual = add(dual, C(non, i));
	for(int i = 1; i <= non; i += 2)homo = add(homo, C(non, i));
	ll tmp = qpow(2, cntd);
	resc = add(homo, dual * oui % mod) * tmp % mod;
	resd = dual * tmp % mod;
	resa = add(qpow(2, n), mod - add(resc, resd));
	if(rev)swap(resa, resb);
	printf("%lld %lld %lld %lld\n", resa, resb, resc, resd);
	return 0;
}
