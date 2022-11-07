#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
ll l, r;
ll k;
bool vis[N];
int main()
{
	scanf("%lld%lld", &l, &r);
	scanf("%lld", &k);
	for(ll i = 2; i * i <= r && i <= k; i++)
	{
		for(ll j = max(i * 2, ((l - 1) / i + 1) * i); j <= r; j += i)
			vis[j - l] = true;
	}
	ll res = 0;
	for(ll i = l; i <= r; i++)
		if(!vis[i - l])res ^= i;
	printf("%lld\n", res);
	return 0;
}