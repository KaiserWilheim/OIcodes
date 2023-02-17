#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
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
ll fac[N], inv[N];
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int sz[N];
ll f[N], g[N];
void dfs1(int p, int fa)
{
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
	}
}
void dfs2(int p, int fa)
{
	int odd = 0;
	f[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs2(e[i], p);
		if(sz[e[i]] & 1)odd++;
		f[p] = f[p] * f[e[i]] % mod;
	}
	if(odd == 0)return;
	f[p] = f[p] * g[odd + (odd & 1)] % mod;
}
signed main()
{
	memset(h, -1, sizeof(h));
	n = 100000;
	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[n] = qpow(fac[n], mod - 2);
	for(int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	g[1] = g[2] = 1;
	for(int i = 3; i <= n; i++)g[i] = (i - 1ll) * g[i - 2] % mod;
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%lld\n", f[1]);
	return 0;
}
