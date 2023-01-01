#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
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
int cnt[N], dcnt[N];
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll f[N];
int main()
{
	scanf("%d", &m), n = 0;
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		n = max(x, n);
		cnt[x]++;
	}
	fac[0] = 1;
	for(int i = 1; i <= m; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[m] = qpow(fac[m], mod - 2);
	for(int i = m; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			dcnt[i] += cnt[j];
	for(int k = 1; k <= 7; k++)
	{
		for(int i = n; i >= 1; i--)
		{
			f[i] = C(dcnt[i], k);
			for(int j = i * 2; j <= n; j += i)
				f[i] = (f[i] - f[j] + mod) % mod;
		}
		if(f[1])
		{
			printf("%d\n", k);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
