#include <bits/stdc++.h>
using namespace std;
const int N = 10000010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int a, d, n;
int mod;
int inv[N];
int fac[N], ifac[N];
int qpow(int a, int x)
{
	int res = 1;
	while(x)
	{
		if(x & 1)res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		x >>= 1;
	}
	return res;
}
void solve()
{
	a = read(), d = read(), n = read();
	if(!d)
	{
		printf("%lld\n", qpow(a, n));
		return;
	}
	int res = 1;
	a = 1ll * a * inv[d] % mod;
	res = 1ll * res * qpow(d, n) % mod;
	if(n + a - 1 >= mod)
	{
		puts("0");
		return;
	}
	res = 1ll * res * fac[a + n - 1] % mod * ifac[a] % mod * a % mod;
	printf("%lld\n", res);
}
int main()
{
	int T;
	scanf("%d", &T);
	scanf("%lld", &mod);
	fac[0] = 1;
	for(int i = 1; i < mod; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i < mod; i++)
		inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod,
		ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
	while(T--)
	{
		solve();
	}
	return 0;
}
