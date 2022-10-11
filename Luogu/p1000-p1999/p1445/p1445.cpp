#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
const ll mod = 1e9 + 7;
ll n;
bool vis[N];
ll prime[N];
void seive()
{
	for(ll i = 2; i <= n; i++)
	{
		if(!vis[i])
			prime[++prime[0]] = i;
		for(ll j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
ll c[N];
int main()
{
	scanf("%lld\n", &n);
	seive();
	for(int i = 1; i <= prime[0]; i++)
	{
		int p = prime[i];
		for(ll j = p; j <= n; j *= p)
			c[i] += (n / j);
		c[i] %= mod;
	}
	ll ans = 1;
	for(int i = 1; i <= prime[0]; i++)
		ans = (ans * (c[i] * 2 + 1) % mod) % mod;
	printf("%lld\n", ans);
	return 0;
}