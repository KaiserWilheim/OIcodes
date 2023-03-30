#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010, M = 1000010;
bool vis[N];
int prime[M];
int phi[N];
void seive(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])prime[++prime[0]] = i, phi[i] = i - 1;
		for(int j = 1; j <= prime[0] && prime[j] * i <= n; j++)
		{
			vis[prime[j] * i] = true;
			if(i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}
}
ll qpow(ll a, ll x, ll mod)
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
ll solve(ll mod)
{
	if(mod == 1)return 0;
	return qpow(2, solve(phi[mod]) + phi[mod], mod);
}
int main()
{
	seive(1e7);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll p;
		scanf("%lld", &p);
		printf("%lld\n", solve(p));
	}
	return 0;
}
