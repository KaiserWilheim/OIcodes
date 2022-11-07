#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
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
int n;
int eine[N], zwei[N];
vector<int>e[N];
void dfs(int p)
{
	if(e[p].empty())
	{
		eine[p] = 1, zwei[p] = 0;
		return;
	}
	int f = 0, g = 0;
	for(auto i : e[p])
	{
		dfs(i);
		f |= (eine[i] == 0);
		g |= (zwei[i] == 0);
	}
	eine[p] = f, zwei[p] = g;
}
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void init()
{
	fac[0] = 1;
	for(int i = 1; i <= 100000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[100000] = qpow(fac[100000], mod - 2);
	for(int i = 99999; i >= 1; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}
int main()
{
	scanf("%d", &n);
	int cnt1 = 0, cnt2 = 0;
	for(int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);
		for(int j = 1; j <= m; j++)
			e[j].clear(), eine[i] = zwei[i] = 0;
		for(int j = 2; j <= m; j++)
		{
			int fa;
			scanf("%d", &fa);
			e[fa].push_back(j);
		}
		dfs(1);
		if(eine[1] * 2 + zwei[1] == 0)cnt2++;
		else if(eine[1] * 2 + zwei[1] == 1)cnt1++;
	}
	init();
	ll ans = (qpow(2, cnt2) - 1) * qpow(2, n - cnt2) % mod;
	if(cnt1)ans = (ans + qpow(2, n - cnt2 - 1)) % mod;
	printf("%lld\n", ans);
	return 0;
}