#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5000010;
int n, m;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
ll mod;
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
ll k;
ll a[N];
ll pre[N], suf[N];
int main()
{
	n = read(), mod = read(), k = read();
	ll ans = 0;
	for(int i = 1; i <= n; i++)
		a[i] = read();
	pre[0] = suf[n + 1] = 1;
	for(int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] * a[i] % mod;
	for(int i = n; i >= 1; i--)
		suf[i] = suf[i + 1] * a[i] % mod;
	ll kk = 1;
	for(int i = 1; i <= n; i++)
	{
		kk = kk * k % mod;
		ans = (ans + kk * pre[i - 1] % mod * suf[i + 1]) % mod;
	}
	ans = ans * qpow(pre[n], mod - 2) % mod;
	printf("%lld\n", ans);
	return 0;
}
