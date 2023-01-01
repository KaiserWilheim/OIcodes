#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define clr(f,n) memset(f,0,(n)*sizeof(ll));
#define cpy(f,g,n) memcpy(f,g,(n)*sizeof(ll));
const int N = 150010;
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
int n;
ll f[N];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%lld", &f[i]);
	invp(f, n);
	for(int i = 0; i < n; i++)
		printf("%lld ", f[i]);
	putchar('\n');
	return 0;
}
