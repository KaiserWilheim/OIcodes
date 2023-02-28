#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2000010;
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
int n;
int prime[N];
int cnt[N];
int vis[N];
void seive(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])prime[++prime[0]] = i, vis[i] = i;
		for(int j = 1; j <= prime[0] && prime[j] * i <= n; j++)
		{
			vis[prime[j] * i] = prime[j];
			if(i % prime[j] == 0)break;
		}
	}
}
int main()
{
	scanf("%d%lld", &n, &mod);
	seive(2e6);
	for(int i = 2; i <= n; i++)cnt[i]--;
	for(int i = n + 2; i <= n + n; i++)cnt[i]++;
	for(int i = n + n; i > 1; i--)
	{
		if(vis[i] < i)
		{
			cnt[vis[i]] += cnt[i];
			cnt[i / vis[i]] += cnt[i];
		}
	}
	ll ans = 1;
	for(int i = 2; i <= 2 * n; i++)
	{
		if(vis[i] == i)
			ans = ans * qpow(i, cnt[i]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
