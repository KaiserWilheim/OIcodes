#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n;
ll a[N], b[N];
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
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	for(int i = 1; i <= n; i++)
		a[i] = (a[i] % b[i] + b[i]) % b[i];
	ll ans = 0;
	ll lcm = 1;
	for(int i = 1; i <= n; i++)
		lcm *= b[i];
	for(int i = 1; i <= n; i++)
	{
		ll k = lcm / b[i];
		ll x, y;
		ll g = exgcd(k, b[i], x, y);
		x = (x % b[i] + b[i]) % b[i];
		ans = (ans + (__int128)k * x % lcm * a[i] % lcm) % lcm;
	}
	ans = (ans % lcm + lcm) % lcm;
	printf("%lld\n", ans);
	return 0;
}