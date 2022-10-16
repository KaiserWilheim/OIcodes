#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n, k;
ll kpd(ll a, ll b)
{
	return b ? kpd(b, a % b) : a;
}
ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}
void solve()
{
	ll a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);
	ll g = kpd(a, b);
	if(c % g != 0)
	{
		puts("-1");
		return;
	}
	ll x, y;
	g = exgcd(a, b, x, y);
	x *= c / g, y *= c / g;
	ll p = b / g, q = a / g;
	ll k;
	if(x < 0)
	{
		k = ceil((1.0 - x) / p);
		x += p * k, y -= q * k;
	}
	else
	{
		k = (x - 1) / p;
		x -= p * k, y += q * k;
	}
	if(y > 0)
	{
		printf("%lld %lld %lld %lld %lld\n", (y - 1) / q + 1, x, (y - 1) % q + 1, x + (y - 1) / q * p, y);
	}
	else
	{
		printf("%lld %lld\n", x, y + q * (ll)ceil((1.0 - y) / q));
	}
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