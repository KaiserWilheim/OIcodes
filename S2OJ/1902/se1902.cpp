#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010, M = 1010;
const ll mod = 1e4 + 7;
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
int n, m, k;
int deg[N];
ll f[N][N];
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
ll C2(ll n) { return n * (n - 1) / 2 % mod; }
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		deg[u]++, deg[v]++;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)cnt += deg[i] & 1;
	f[0][cnt] = 1;
	for(int i = 1; i <= k; i++)
		for(int j = 0; j <= n; j++)
			f[i][j] = add(add(f[i - 1][j + 2] * C2(j + 2) % mod, f[i - 1][j] * j * (n - j)) % mod, add(j >= 2 ? f[i - 1][j - 2] * C2(n - j + 2) % mod : 0, mod - (i >= 2 ? f[i - 2][j] * (C2(n) - i + 2) : 0) % mod)) * qpow(i, mod - 2) % mod;
	printf("%lld\n", f[k][0]);
	return 0;
}
