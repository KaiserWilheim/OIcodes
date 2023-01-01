#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define clr(f,n) memset(f,0,(n)*sizeof(ll));
#define cpy(f,g,n) memcpy(f,g,(n)*sizeof(ll));
const int N = 270010;
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
int tr[N], tf;
void initr(int n)
{
	if(tf == n)return;
	tf = n;
	for(int i = 0; i < n; i++)
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
}
void NTT(ll *g, bool op, int n)
{
	initr(n);
	static ull f[N], w[N] = { 1 };
	for(int i = 0; i < n; i++)f[i] = ((mod << 5) + g[tr[i]]) % mod;
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
void mul(ll *f, ll *g, int n)
{
	for(int i = 0; i < n; i++)
		f[i] = f[i] * g[i] % mod;
}
void timep(ll *f, ll *g, int m, int lim)
{
	static ll sav[N];
	int n = 1;
	while(n < m + m)n <<= 1;
	clr(sav, n); cpy(sav, g, n);
	NTT(f, 1, n); NTT(sav, 1, n);
	mul(f, sav, n); NTT(f, 0, n);
	clr(f + lim, n - lim); clr(sav, n);
}
void invp(ll *f, int m)
{
	int n = 1;
	while(n < m)n <<= 1;
	static ll w[N], r[N], sav[N];
	w[0] = qpow(f[0]);
	for(int len = 2; len <= n; len <<= 1)
	{
		for(int i = 0; i < (len >> 1); i++)r[i] = w[i];
		cpy(sav, f, len); NTT(sav, 1, len);
		NTT(r, 1, len); mul(r, sav, len);
		NTT(r, 0, len); clr(r, len >> 1);
		cpy(sav, w, len); NTT(sav, 1, len);
		NTT(r, 1, len); mul(r, sav, len);
		NTT(r, 0, len);
		for(int i = len >> 1; i < len; i++)
			w[i] = (w[i] * 2 - r[i] + mod) % mod;
	}
	cpy(f, w, m);
	clr(sav, n); clr(w, n); clr(r, n);
}
ll inv[N];
void initi(int lim)
{
	inv[1] = 1;
	for(int i = 2; i <= lim; i++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
void derp(ll *f, int m)
{
	for(int i = 1; i < m; i++)
		f[i - 1] = f[i] * i % mod;
	f[m - 1] = 0;
}
void intp(ll *f, int m)
{
	for(int i = m; i; i--)
		f[i] = f[i - 1] * inv[i] % mod;
	f[0] = 0;
}
void lnp(ll *f, int m)
{
	static ll g[N];
	cpy(g, f, m);
	invp(g, m); derp(f, m);
	timep(f, g, m, m);
	intp(f, m - 1);
	clr(g, m);
}
void exp(ll *f, int m)
{
	static ll s[N], s2[N];
	int n = 1;
	while(n < m)n <<= 1;
	s2[0] = 1;
	for(int len = 2; len <= n; len <<= 1)
	{
		cpy(s, s2, len >> 1);
		lnp(s, len);
		for(int i = 0; i < len; i++)s[i] = (f[i] - s[i] + mod) % mod;
		s[0] = (s[0] + 1) % mod;
		timep(s2, s, len, len);
	}
	cpy(f, s2, m);
	clr(s, n); clr(s2, n);
}
int n;
ll f[N];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%lld", &f[i]);
	initi(n);
	exp(f, n);
	for(int i = 0; i < n; i++)
		printf("%lld ", f[i]);
	putchar('\n');
	return 0;
}
