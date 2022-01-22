#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10;
const int mod = 998244353;//模数
int G = 3, invG;
int n, m;
int f[5 * N], g[N * 5];
int sav[N * 5];
int w[N * 5];
int exp_sav[N * 5], exp_g[N * 5];

//计算需要部分

int qpow(int a, int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}//快速幂

int tr[N * 5];

int add(int a, int b)
{
	return a + b >= mod ? a + b - mod : a + b;
}//防溢出加法

int sub(int a, int b)
{
	return a - b < 0 ? a - b + mod : a - b;
}//防溢出减法

void ntt(int *f, int n, int op)
{
	for(int i = 0; i < n; ++i)
	{
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
	}
	for(int i = 0; i < n; ++i)
	{
		if(i < tr[i]) swap(f[i], f[tr[i]]);
	}
	for(int p = 2; p <= n; p <<= 1)
	{
		int len = p / 2;
		int tG = qpow(op ? G : invG, (mod - 1) / p);
		for(int l = 0; l < n; l += p)
		{
			int buf = 1;
			for(int k = l; k < l + len; ++k)
			{
				int tmp = buf * f[k + len] % mod;
				f[k + len] = sub(f[k], tmp);
				f[k] = add(f[k], tmp);
				buf = buf * tG % mod;
			}//看起来有点像容斥？
		}
	}
	if(op == 0)
	{
		int invn = qpow(n, mod - 2);
		for(int i = 0; i < n; ++i)
		{
			f[i] = f[i] * invn % mod;
		}
	}
}//数组快速乘法

int mul_sav[N * 5];

int fac[N * 5], ifac[N * 5], inv[N * 5];

void px(int *f, int *g, int n)
{
	for(int i = 0; i < n; ++i) f[i] = f[i] * g[i] % mod;
}//数组相乘

void clr(int *f, int n)
{
	for(int i = 0; i < n; ++i) f[i] = 0;
}//清空数组

void cpy(int *f, int *g, int n)
{
	for(int i = 0; i < n; ++i) f[i] = g[i];
}//数组复制

void mul(int *f, int *g, int len)
{
	int n;
	for(n = 1; n < len + len; n <<= 1);
	cpy(mul_sav, g, len);
	ntt(f, n, 1), ntt(mul_sav, n, 1);
	px(f, mul_sav, n);
	ntt(f, n, 0);
	for(int i = len; i < n; ++i) f[i] = 0;
	clr(mul_sav, n);
}

void invp(int *f, int n)
{
	int m = n;
	for(n = 1; n < m; n <<= 1);
	g[0] = qpow(f[0], mod - 2);
	for(int len = 2; len <= n; len <<= 1)
	{
		for(int i = 0; i < (len >> 1); ++i) w[i] = (g[i] << 1) % mod;
		cpy(sav, f, len);
		ntt(g, len << 1, 1), px(g, g, len << 1);
		ntt(sav, len << 1, 1), px(g, sav, len << 1);
		ntt(g, len << 1, 0), clr(g + len, len);
		for(int i = 0; i < len; ++i)
		{
			g[i] = (w[i] - g[i] + mod) % mod;
		}
	}
	cpy(f, g, m), clr(g, n + n), clr(w, n + n), clr(sav, n + n);
}

void dao(int *f, int n)
{
	for(int i = 1; i < n; ++i)
	{
		f[i - 1] = f[i] * i % mod;
	}
	f[n - 1] = 0;
}//求导

void ji(int *f, int n)
{
	for(int i = n - 1; i; --i)
	{
		f[i] = f[i - 1] * qpow(i, mod - 2) % mod;
	}
	f[0] = 0;
}//积分

int ln_sav[N * 5], ln_w[N * 5];

void ln(int *f, int n)
{
	cpy(ln_sav, f, n);
	cpy(ln_w, f, n);
	invp(ln_w, n), dao(ln_sav, n);
	mul(ln_w, ln_sav, n);
	ji(ln_w, n);
	cpy(f, ln_w, n);
}//求对数

void exp(int *f, int n)
{
	int m = n;
	for(n = 1; n < m; n <<= 1);
	exp_g[0] = 1;
	for(int len = 2; len <= n; len <<= 1)
	{
		cpy(exp_sav, exp_g, len);
		ln(exp_sav, len);
		for(int i = 0; i < len; ++i) exp_sav[i] = (f[i] + mod - exp_sav[i]) % mod;
		exp_sav[0] = (exp_sav[0] + 1) % mod;
		ntt(exp_g, len << 1, 1), ntt(exp_sav, len << 1, 1);
		px(exp_g, exp_sav, len << 1);
		ntt(exp_g, len << 1, 0);
		clr(exp_g + len, len);
	}cpy(f, exp_g, m), clr(exp_sav, n), clr(exp_g, n);
}//求指数


int C(int n, int m)
{
	if(m > n || m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}//组合数

//解决问题部分

void solve1()
{
	cout << qpow(m, n) << '\n';
}

void solve2()
{
	cout << C(m, n) * fac[n] % mod << '\n';
}

void solve3()
{
	int res = 0;
	for(int i = 0; i <= m; ++i)
	{
		if(i & 1)
			res = sub(res, C(m, i) * qpow((m - i), n) % mod);
		else
			res = add(res, C(m, i) * qpow((m - i), n) % mod);
	}
	cout << res << '\n';
}

void solve4()
{
	for(int i = 0; i <= n; ++i)
	{
		f[i] = 1ll * qpow(i, n) * ifac[i] % mod;
		if(i & 1) g[i] = sub(mod, ifac[i]);
		else g[i] = ifac[i];
	}
	mul(f, g, n + 1);
	int res = 0;
	for(int i = 0; i <= m; ++i)
	{
		res = add(res, f[i]);
	}
	cout << res << '\n';
}

void solve5()
{
	cout << (n <= m) << '\n';
}

void solve6()
{
	int res = 0;
	for(int i = 0; i <= m; ++i)
	{
		if(i & 1)
		{
			res = sub(res, C(m, i) * qpow(m - i, n) % mod);
		}
		else res = add(res, C(m, i) * qpow(m - i, n) % mod);
	}
	cout << res * ifac[m] % mod << '\n';
}

void solve7()
{
	cout << C(n + m - 1, m - 1) << '\n';
}

void solve8()
{
	cout << C(m, n) << '\n';
}

void solve9()
{
	cout << C(n - 1, m - 1) << '\n';
}

void solve10()
{
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	memset(mul_sav, 0, sizeof(mul_sav));
	for(int i = 1; i <= m; ++i)
	{
		for(int j = 1; j <= n / i; ++j)
		{
			f[j * i - 1] = add(f[j * i - 1], i);
		}
	}
	ji(f, n + 1);
	exp(f, n + 1);
	cout << f[n] << '\n';
}

void solve11()
{
	cout << (n <= m) << '\n';
}

void solve12()
{
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	memset(mul_sav, 0, sizeof(mul_sav));
	memset(sav, 0, sizeof(sav));
	memset(ln_w, 0, sizeof(ln_w));
	memset(exp_g, 0, sizeof(exp_g));
	memset(ln_sav, 0, sizeof(ln_w));
	memset(w, 0, sizeof(w));
	n -= m;
	if(n < 0)
	{
		puts("0");
		return;
	}
	solve10();
}

signed main()
{
	cin >> n >> m;
	invG = qpow(G, mod - 2);
	ifac[0] = fac[0] = ifac[1] = fac[1] = inv[1] = 1;
	for(int i = 2; i <= 400000; ++i)
	{
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
	solve1();
	solve2();
	solve3();
	solve4();
	solve5();
	solve6();
	solve7();
	solve8();
	solve9();
	solve10();
	solve11();
	solve12();
	return 0;
}
