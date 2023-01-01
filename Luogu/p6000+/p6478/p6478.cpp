#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = N << 1;
const ll mod = 998244353;
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
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
char s[N];
int a[N];
int sz[N], sum[N];
ll f[N][N];
ll g[N];
void dfs(int p, int fa)
{
	sz[p] = 1, sum[p] = a[p];
	f[p][0] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		int v = e[i];
		dfs(v, p);
		for(int j = 0; j <= sz[p] + sz[v]; j++)g[j] = 0;
		for(int j = 0; j <= min(sz[p], n / 2); j++)
			for(int k = 0; k <= min(sz[v], n / 2 - j); k++)
				g[j + k] = (g[j + k] + f[p][j] * f[v][k] % mod) % mod;
		for(int j = 0; j <= sz[p] + sz[v]; j++)
			f[p][j] = g[j];
		sz[p] += sz[v], sum[p] += sum[v];
	}
	for(int i = min(sum[p], sz[p] - sum[p]); i; i--)
	{
		if(a[p] == 1)f[p][i] = (f[p][i] + f[p][i - 1] * (sz[p] - sum[p] - (i - 1)) % mod) % mod;
		else f[p][i] = (f[p][i] + f[p][i - 1] * (sum[p] - (i - 1)) % mod) % mod;
	}
}

int main()
{
	memset(h, -1, sizeof(h));
	fac[0] = 1;
	for(int i = 1; i <= 5000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[5000] = qpow(fac[5000]);
	for(int i = 4999; i; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
		a[i] = s[i] - '0';
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dfs(1, 0);
	for(int i = 0; i <= n / 2; i++)
		f[1][i] = f[1][i] * fac[n / 2 - i] % mod;
	for(int i = 0; i <= n / 2; i++)
	{
		ll ans = 0;
		for(int j = i; j <= n / 2; j++)
		{
			if((j - i) & 1)ans = (ans - C(j, i) * f[1][j] % mod + mod) % mod;
			else ans = (ans + C(j, i) * f[1][j] % mod) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
