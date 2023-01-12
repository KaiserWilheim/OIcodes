#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 400010;
ll n, x;
bool chq(ll x)
{
	ll now = 0, ans = 0;
	for(int i = 61; i >= 0; i--)
	{
		if(n & (1ll << i))
		{
			ll k = (now + 1) << (i + 1);
			if(x < k)ans += (1ll << i);
		}
		now <<= 1;
		if(n & (1ll << i))now++;
	}
	return (ans | ::x) > ::x;
}
bool chq2(ll x)
{
	ll now = 0, ans = 0;
	for(int i = 61; i >= 0; i--)
	{
		if((n >> i) & 1)
		{
			ll k = (now + 1) << (i + 1);
			if(x < k)ans += (1ll << i);
		}
		now <<= 1;
		if(n & (1ll << i))now++;
	}
	return ans == ::x;
}
void solve()
{
	scanf("%lld%lld", &n, &x);
	if((n & x) != x)
	{
		puts("-1");
		return;
	}
	if(n == x)
	{
		printf("%lld\n", n);
		return;
	}
	ll r = 2e18, l = n;
	ll ans = l;
	while(l <= r)
	{
		ll mid = (l + r) >> 1;
		if(chq(mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	if(chq2(ans + 1))printf("%lld\n", ans + 1);
	else puts("-1");
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
