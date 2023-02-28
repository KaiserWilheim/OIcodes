#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5050;
const ll mod = 1e9 + 7;
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
ll fac[N], inv[N];
ll C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
int n;
vector<int>e[N];
ll f[N][N];
int sz[N];
ll tmp[N];
void dfs(int p, int fa)
{
	sz[p] = 1;
	f[p][1] = 1;
	for(auto v : e[p])
	{
		if(v == fa)continue;
		dfs(v, p);
		for(int i = sz[p]; ~i; i--)
			for(int j = 0; j <= sz[v]; j++)
				tmp[i + j] = add(tmp[i + j], C(i + j - 1, i - 1) * f[p][i] % mod * f[v][j] % mod);
		sz[p] += sz[v];
		for(int i = 0; i <= sz[p]; i++)
			f[p][i] = tmp[i], tmp[i] = 0;
	}
	for(int i = sz[p]; ~i; i--)
		f[p][i] = add(f[p][i + 1], f[p][i]);
}
int main()
{
	n = 5000;
	fac[0] = 1;
	for(int i = 1; i <= n; i++)fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n] = qpow(fac[n], mod - 2);
	for(int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	printf("%lld\n", f[1][1]);
	return 0;
}
