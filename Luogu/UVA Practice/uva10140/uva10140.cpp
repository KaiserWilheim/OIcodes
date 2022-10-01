#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll g = exgcd(b, a % b, x, y);
	ll t = x;
	x = y;
	y = t - (a / b) * y;
	return g;
}
int main()
{
	ll a, b, x, y;
	while(~scanf("%lld%lld", &a, &b))
	{
		ll g = exgcd(a, b, x, y);
		printf("%lld %lld %lld\n", x, y, g);
	}
	return 0;
}