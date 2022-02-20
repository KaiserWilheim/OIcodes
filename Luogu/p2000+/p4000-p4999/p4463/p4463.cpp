#include<bits/stdc++.h>
#define N 2053
#define ll long long
#define reg register
#define plus(x,y) (x+y>=p?x+y-p:x+y)
#define minus(x,y) (x<y?x-y+p:x-y)
#define pi 3.14159265358979323
using namespace std;
int p;
//快读快写
inline void read(int &x)
{
	x = 0;
	char c = getchar();
	while(c < '0' || c>'9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}
void print(int x)
{
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
//
inline int qpow(int a, int t)
{//快速幂
	int res = 1;
	while(t)
	{
		if(t & 1) res = ( ll )res * a % p;
		a = ( ll )a * a % p;
		t >>= 1;
	}
	return res;
}
struct CP//复数结构体
{
	double r, i;
	inline CP(double r = 0, double i = 0) :r(r), i(i) {}
	inline CP operator ~ () const
	{//共轭
		return CP(r, -i);
	}
	//四则运算之三
	inline CP operator + (const CP &x) const
	{
		return CP(r + x.r, i + x.i);
	}
	inline CP operator - (const CP &x) const
	{
		return CP(r - x.r, i - x.i);
	}
	inline CP operator * (const CP &x) const
	{
		return CP(r * x.r - i * x.i, i * x.r + r * x.i);
	}
	//乘以一个整数
	inline CP operator / (const int &x) const
	{
		return CP(r / x, i / x);
	}
};
int rev[N], inv[N], fac[N], ifac[N];
CP rt[N];//单位根
int siz;
void init(int n)//预处理
{
	int lim = 1;
	while(lim <= n) lim <<= 1, ++siz;
	for(reg int i = 1; i != lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (siz - 1));
	inv[1] = 1;
	rt[lim >> 1] = CP(1, 0);
	for(reg int i = 1; i != (lim >> 1); ++i) rt[i + (lim >> 1)] = CP(cos(pi * i / lim * 2), sin(pi * i / lim * 2));
	for(reg int i = (lim >> 1) - 1; i; --i) rt[i] = rt[i << 1];
	for(reg int i = 2; i <= lim; ++i) inv[i] = ( ll )(p - p / i) * inv[p % i] % p;
}
inline int getlen(int n)
{
	return 1 << (32 - __builtin_clz(n));
}
inline void FFT(CP *f, int type, int lim)
{//fft
	if(type == -1) reverse(f + 1, f + lim);
	static CP a[N], x;
	int shift = siz - __builtin_ctz(lim);
	for(reg int i = 0; i != lim; ++i) a[rev[i] >> shift] = f[i];
	for(reg int mid = 1; mid != lim; mid <<= 1)
		for(reg int j = 0; j != lim; j += (mid << 1))
			for(reg int k = 0; k != mid; ++k)
			{
				x = a[j | k | mid] * rt[mid | k];
				a[j | k | mid] = a[j | k] - x;
				a[j | k] = a[j | k] + x;
			}
	for(reg int i = 0; i != lim; ++i) f[i] = a[i];
	if(type == 1) return;
	for(reg int i = 0; i != lim; ++i) f[i] = f[i] / lim;
}
void multiply(const int *A, const int *B, int n, int m, int *R, int len)
{
	static CP f[N], g[N], h[N], q[N];
	register CP t, f0, f1, g0, g1;
	register ll x, y, z;
	int lim = getlen(n + m);
	for(reg int i = 0; i != lim; ++i)
	{
		f[i] = CP(A[i] >> 15, A[i] & 32767);
		g[i] = CP(B[i] >> 15, B[i] & 32767);
	}
	FFT(f, 1, lim), FFT(g, 1, lim);
	for(reg int i = 0; i != lim; ++i)
	{
		t = ~f[i ? lim - i : 0];
		f0 = (f[i] - t) * CP(0, -0.5), f1 = (f[i] + t) * 0.5;
		t = ~g[i ? lim - i : 0];
		g0 = (g[i] - t) * CP(0, -0.5), g1 = (g[i] + t) * 0.5;
		h[i] = f1 * g1;
		q[i] = f1 * g0 + f0 * g1 + f0 * g0 * CP(0, 1);
	}
	FFT(h, -1, lim), FFT(q, -1, lim);
	for(reg int i = 0; i <= len; ++i)
	{
		x = ( ll )(h[i].r + 0.5) % p << 30;
		y = ( ll )(q[i].r + 0.5) << 15;
		z = q[i].i + 0.5;
		R[i] = (x + y + z) % p;
	}
}
inline void inverse(const int *f, int n, int *R)
{
	static int g[N], h[N];
	memset(g, 0, getlen(n << 1) << 2);
	int lim = 1, top = 0;
	int s[30];
	while(n)
	{
		s[++top] = n;
		n >>= 1;
	}
	g[0] = qpow(f[0], p - 2);
	while(top--)
	{
		n = s[top + 1];
		while(lim <= (n << 1)) lim <<= 1;
		memcpy(h, f, (n + 1) << 2);
		memset(h + n + 1, 0, (lim - n) << 2);
		multiply(h, g, n, n, h, n);
		multiply(h, g, n, n, h, n);
		for(reg int i = 0; i <= n; ++i) g[i] = minus(plus(g[i], g[i]), h[i]);
	}
	memcpy(R, g, (n + 1) << 2);
}
inline void log(int *f, int n)
{
	static int g[N];
	inverse(f, n, g);
	for(reg int i = 0; i != n; ++i) f[i] = ( ll )f[i + 1] * (i + 1) % p;
	f[n] = 0;
	int lim = getlen(n << 1);
	memset(g + n + 1, 0, (lim - n) << 2);
	multiply(f, g, n, n, f, n);
	for(reg int i = n; i; --i) f[i] = ( ll )f[i - 1] * inv[i] % p;
	f[0] = 0;
}
void exp(const int *f, int n, int *R)
{
	static int g[N], h[N];
	memset(g, 0, getlen(n << 1) << 2);
	int lim = 1, top = 0;
	int s[30];
	while(n)
	{
		s[++top] = n;
		n >>= 1;
	}
	g[0] = 1;
	while(top--)
	{
		n = s[top + 1];
		while(lim <= (n << 1)) lim <<= 1;
		memcpy(h, g, lim << 2);
		log(g, n);
		for(reg int i = 0; i <= n; ++i) g[i] = minus(f[i], g[i]);
		g[0] = plus(g[0], 1);
		multiply(g, h, n, n, g, n);
	}
	memcpy(R, g, (n + 1) << 2);
}
int n, k;
int F[N], G[N];
int main()
{
	read(k), read(n), read(p);
	init(n << 1 | 1);
	int ans, lim = getlen(n << 1), pw = k;
	ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
	for(reg int i = 2; i <= n + 1; ++i) ifac[i] = fac[i] = ( ll )fac[i - 1] * i % p;
	ifac[n + 1] = qpow(fac[n + 1], p - 2);
	for(reg int i = n; i; --i) ifac[i] = ( ll )ifac[i + 1] * (i + 1) % p;
	for(reg int i = 0; i <= n; ++i)
	{
		F[i] = ( ll )pw * ifac[i + 1] % p;
		G[i] = (i & 1) ? p - ifac[i + 1] : ifac[i + 1];
		pw = ( ll )pw * k % p;
	}
	inverse(G, n, G);
	multiply(F, G, n, n, G, n);
	memset(F, 0, sizeof(F));
	for(reg int i = 1; i <= n; ++i)
	{
		F[i] = ( ll )fac[i - 1] * G[i] % p;
		if((i - 1) & 1) F[i] = p - F[i];
	}
	exp(F, n, F);
	ans = ( ll )F[n] * fac[n] % p;
	printf("%d", ans);
	return 0;
}
