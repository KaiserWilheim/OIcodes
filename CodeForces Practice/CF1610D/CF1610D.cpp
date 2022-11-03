#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
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
int n;
int a[N];
int cnt[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		cnt[__builtin_ctz(a[i])]++;
	}
	ll ans = 0;
	int sum = 0;
	for(int i = 1; i <= 30; i++)sum += cnt[i];
	ans = (qpow(2, cnt[0]) - 1) * qpow(2, sum) % mod;
	for(int i = 1; i <= 30; i++)
	{
		sum = 0;
		for(int j = i + 1; j <= 30; j++)sum += cnt[j];
		ll res = 0;
		if(cnt[i] >= 2)res = qpow(2, cnt[i] - 1) - 1;
		ans = (ans + res * qpow(2, sum) % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
