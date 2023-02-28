#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
const ll mod = 998244353;
ll inv2,inv3, inv32;
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
int n, m;
int p[N], sz[N];
ll val[N], tag[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
vector<int>g[N];
ll pw[N];
void soyuz(int u, int v)
{
	ll tag1 = inv2, tag2 = inv32;
	if(g[u].size() > g[v].size())
	{
		swap(g[u], g[v]);
		swap(sz[u], sz[v]);
		swap(tag[u], tag[v]);
		tag1 = 2, tag2 = inv3;
	}
	ll k = qpow(tag[v], mod - 2) * tag[u] % mod;
	for(auto i : g[u])
	{
		val[i] = val[i] * tag1 % mod * k % mod;
		g[v].push_back(i);
	}
	sz[v] += sz[u];
	p[u] = v;
	g[u].clear();
	tag[v] = tag[v] * tag2 % mod;
}
int main()
{
	inv2 = qpow(2, mod - 2);
	inv3 = qpow(3, mod - 2);
	inv32 = inv3 * 2 % mod;
	scanf("%d%d", &n, &m);
	pw[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		p[i] = i, sz[i] = 1;
		g[i].push_back(i);
		val[i] = 1, tag[i] = 1;
		pw[i] = pw[i - 1] * 3 % mod;
	}
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			soyuz(v, u);
		}
		else
		{
			int x;
			scanf("%d", &x);
			int y = find(x);
			ll res = pw[sz[y]] * val[x] % mod * tag[y] % mod * pw[n - sz[y]] % mod;
			printf("%lld\n", res);
		}
	}
	return 0;
}
