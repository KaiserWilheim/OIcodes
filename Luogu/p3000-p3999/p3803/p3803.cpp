#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
const int N = 2100010;
const ll G = 3, mod = 998244353;
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
const ll invG = qpow(G);
int tr[N];
void ntt(ll *g, bool op, int n)
{
	static ull f[N], w[N] = { 1 };
	for(int i = 0; i < n; i++)f[i] = g[tr[i]];
	for(int l = 1; l < n; l <<= 1)
	{
		ull tmpG = qpow(op ? G : invG, (mod - 1) / (l * 2));
		for(int i = 1; i < l; i++)w[i] = w[i - 1] * tmpG % mod;
		for(int k = 0; k < n; k += l * 2)
		{
			for(int p = 0; p < l; p++)
			{
				ll tmp = w[p] * f[k | l | p] % mod;
				f[k | l | p] = f[k | p] + mod - tmp;
				f[k | p] = f[k | p] + tmp;
			}
		}
		if(l == (1 << 10))
			for(int i = 0; i < n; i++)f[i] %= mod;
	}
	if(!op)
	{
		ull invn = qpow(n);
		for(int i = 0; i < n; i++)g[i] = f[i] % mod * invn % mod;
	}
	else
	{
		for(int i = 0; i < n; i++)g[i] = f[i] % mod;
	}
}
int n, m;
ll f[N], g[N];
int main()
{
	scanf("%d%d", &n, &m);
	n++, m++;
	for(int i = 0; i < n; i++)
		scanf("%lld", &f[i]);
	for(int i = 0; i < m; i++)
		scanf("%lld", &g[i]);
	int len = 1;
	while(len < n + m)len <<= 1;
	for(int i = 0; i < len; i++)
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? len >> 1 : 0);
	ntt(f, 1, len), ntt(g, 1, len);
	for(int i = 0; i < len; i++)
		f[i] = f[i] * g[i] % mod;
	ntt(f, 0, len);
	for(int i = 0; i < n + m - 1; i++)
		printf("%lld ", f[i]);
	putchar('\n');
	return 0;
}
