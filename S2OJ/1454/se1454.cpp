#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll mod = 1e9 + 7;
ll qpow(ll a, int x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
int n, m, q;
ll pv[N], sv[N], ans[N];
int l[N], r[N];
int h[N], e[M], ne[M], idx;
ll w[N];
vector<int>vl[N], vr[N];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll tr[N];
int lowbit(int x)
{
	return x & -x;
}
void segadd(int x, ll c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] = (tr[i] + c) % mod;
	return;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res = (res + tr[i]) % mod;
	return res;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
	{
		ll a, b;
		scanf("%lld%lld", &a, &b);
		pv[i] = (a * qpow(b, mod - 2)) % mod;
		sv[i] = (sv[i - 1] + pv[i]) % mod;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		ll w = (pv[u] * pv[v]) % mod;
		add(u, v, w);
	}
	for(int i = 1; i <= q; i++)
	{
		scanf("%d%d", &l[i], &r[i]);
		vl[l[i]].push_back(i);
		vr[r[i]].push_back(i);
		ans[i] = (sv[r[i]] - sv[l[i] - 1] + mod) % mod;
	}
	for(int i = 1; i <= n; i++)
	{
		for(auto j : vl[i])
			ans[j] = (ans[j] + segsum(r[j]) - segsum(l[j] - 1) + mod) % mod;
		for(int j = h[i]; ~j; j = ne[j])
			segadd(e[j], w[j]);
		for(auto j : vr[i])
			ans[j] = (ans[j] + segsum(l[j] - 1) - segsum(r[j]) + mod) % mod;
	}
	for(int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}