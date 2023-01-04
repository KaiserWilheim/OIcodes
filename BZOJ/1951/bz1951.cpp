#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
const int mod = 999911658;
int kpd(int a, int b)
{
	return b ? kpd(b, a % b) : a;
}
int fac[N], inv[N];
int a[5], b[5] = { 0,2,3,4679,35617 };
int qpow(int a, int x, int p)
{
	int res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;
	}
	return res;
}
void init(int p)
{
	fac[0] = 1;
	for(int i = 1; i < p; i++)
		fac[i] = fac[i - 1] * i % p;
	inv[p - 1] = qpow(fac[p - 1], p - 2, p);
	for(int i = p - 1; i > 1; i--)
		inv[i - 1] = inv[i] * i % p;
	inv[0] = 1;
}
int C(int n, int m, int p)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % p * inv[n - m] % p;
}
int lucas(int n, int m, int p)
{
	if(n < m)return 0;
	if(!n)return 1;
	return lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}
signed main()
{
	int n, g;
	scanf("%lld%lld", &n, &g);
	if(g % (mod + 1) == 0)
	{
		puts("0");
		return 0;
	}
	for(int k = 1; k <= 4; k++)
	{
		init(b[k]);
		for(int i = 1; i * i <= n; i++)
		{
			if(n % i == 0)
			{
				a[k] = (a[k] + lucas(n, i, b[k])) % b[k];
				if(i * i != n)
					a[k] = (a[k] + lucas(n, n / i, b[k])) % b[k];
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= 4; i++)
		ans = (ans + a[i] * (mod / b[i]) % mod * qpow(mod / b[i], b[i] - 2, b[i])) % mod;
	printf("%lld\n", qpow(g, ans, mod + 1));
	return 0;
}