#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5010, M = N << 1;
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
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n, m;
int L[N], R[N];
ll f[N][N];
ll fac[M], inv[M];
void init()
{
	fac[0] = 1;
	for(int i = 1; i <= 10000; i++)fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[10000] = qpow(fac[10000], mod - 2);
	for(int i = 10000; i > 1; i--)inv[i - 1] = inv[i] * i % mod;
}
ll A(int n, int m)
{
	if(n < 0 || m < 0 || n < m)return 0;
	return fac[n] * inv[n - m] % mod;
}
int main()
{
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		L[u]++, R[v]++;
	}
	for(int i = 1; i <= m; i++)L[i] += L[i - 1], R[i] += R[i - 1];
	f[0][0] = 1;
	for(int i = 1; i <= m; i++)
	{
		for(int j = 0; j <= min(i, R[i - 1]); j++)
		{
			f[i][j] = add(f[i][j], f[i - 1][j] * A(i - j - L[i - 1], L[i] - L[i - 1]) % mod);
			f[i][j + 1] = add(f[i][j + 1], f[i - 1][j] * (R[i] - j) % mod * A(i - j - 1 - L[i - 1], L[i] - L[i - 1]) % mod);
		}
	}
	printf("%lld\n", f[m][n]);
	return 0;
}
