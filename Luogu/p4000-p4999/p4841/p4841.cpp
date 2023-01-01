#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define clr(f,n) memset(f,0,(n)*sizeof(ll));
#define cpy(f,g,n) memcpy(f,g,(n)*sizeof(ll));
#define rev(f,n) reverse(f,f+(n));
const int N = 270010;
const ll G = 3, mod = 1004535809;
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

int n, m;
ll f[N], g[N];
ll fac[N], inv[N];
int main()
{
	scanf("%d", &n);
	n++;
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n] = qpow(fac[n]);
	for(int i = n - 1; i; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	g[0] = 1;
	for(int i = 1; i < n; i++)
	{
		ll tmp = qpow(2, 1ll * i * (i - 1) / 2 % (mod - 1));
		f[i] = tmp * inv[i - 1] % mod;
		g[i] = tmp * inv[i] % mod;
	}
	invp(g, n);
	timep(f, g, n, n);
	int w = 1;
	while(w < n)w <<= 1;
	ll res = f[n - 1] * fac[n - 2] % mod;
	printf("%lld\n", res);
	return 0;
}
