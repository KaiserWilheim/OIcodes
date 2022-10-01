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
	int T;
	scanf("%d", &T);
	for(int _i = 1; _i <= T; _i++)
	{
		ll a, b, c, p;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &p);
		ll x, y, ans = 0;
		ll g = exgcd(exgcd(a, b, x, y), c, x, y);
		if(p % g != 0)
		{
			printf("Case %d: 0\n", _i);
			continue;
		}
		ll s = exgcd(a / g, b / g, x, y);
		ll x0 = x, y0 = y;
		ll x1, y1;
		for(ll z = 0;; z++)
		{
			if(p < z * c)break;
			ll d = p / g - c / g * z;
			if(d % s != 0)continue;
			x1 = x0 * d / s, y1 = y0 * d / s;
			ans += (ll)floor(x1 * g * 1.0 * s * 1.0 / b) - (ll)ceil(-y1 * g * 1.0 * s * 1.0 / a) + 1;
		}
		printf("Case %d: %lld\n", _i, ans);
	}
	return 0;
}