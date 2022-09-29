#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 60;
const ll bs1 = 19260817, bs2 = 19491001;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x)
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
int n;
ll ha[N][N], hb[N][N];
ll geta(int x, int y, int k)
{
	ll res = ha[x][y];
	res = (res - ha[x][y - k] * qpow(bs1, k) % mod - ha[x - k][y] * qpow(bs2, k) % mod) % mod + mod;
	res = (res + ha[x - k][y - k] * qpow(bs1, k) % mod * qpow(bs2, k) % mod) % mod;
	return res;
}
ll getb(int x, int y, int k)
{
	ll res = hb[x][y];
	res = (res - hb[x][y - k] * qpow(bs1, k) % mod - hb[x - k][y] * qpow(bs2, k) % mod) % mod + mod;
	res = (res + hb[x - k][y - k] * qpow(bs1, k) % mod * qpow(bs2, k) % mod) % mod;
	return res;
}
set<ll>s[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%lld", &ha[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%lld", &hb[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			ha[i][j] = (ha[i][j - 1] * bs1 + ha[i][j]) % mod;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			hb[i][j] = (hb[i][j - 1] * bs1 + hb[i][j]) % mod;
	for(int j = 1; j <= n; j++)
		for(int i = 1; i <= n; i++)
			ha[i][j] = (ha[i - 1][j] * bs2 + ha[i][j]) % mod;
	for(int j = 1; j <= n; j++)
		for(int i = 1; i <= n; i++)
			hb[i][j] = (hb[i - 1][j] * bs2 + hb[i][j]) % mod;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= min(i, j); k++)
				s[k].insert(geta(i, j, k));
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= min(i, j); k++)
				if(s[k].count(getb(i, j, k)))
					ans = max(ans, k);
	printf("%d\n", ans);
	return 0;
}