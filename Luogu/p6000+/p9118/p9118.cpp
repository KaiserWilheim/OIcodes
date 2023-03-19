#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
ll n;
int k;
bool vis[N];
int main()
{
	scanf("%lld%d", &n, &k);
	if(k <= 1)
	{
		printf("%lld\n", n);
		return 0;
	}
	if(k == 2)
	{
		ll ans = sqrtl(n);
		for(ll i = 2; i <= min<ll>(n, 1e6); i++)
		{
			if(vis[i])continue;
			ll x = i * i;
			for(int j = 2; x <= n; j++)
			{
				if(x <= 1e6)vis[x] = true;
				if((j >= k) && (j & 1))ans++;
				if(n / i < x)break;
				x = x * i;
			}
		}
		printf("%lld\n", ans);
	}
	else
	{
		ll ans = 1;
		for(ll i = 2; i <= min<ll>(n, 1e6); i++)
		{
			if(vis[i])continue;
			ll x = i * i;
			for(int j = 2; x <= n; j++)
			{
				if(x <= 1e6)vis[x] = true;
				if(j >= k)ans++;
				if(n / i < x)break;
				x = x * i;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
