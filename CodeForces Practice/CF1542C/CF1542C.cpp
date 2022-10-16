#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
const ll mod = 1e9 + 7;
ll n;
ll kpd(ll a, ll b)
{
	return b ? kpd(b, a % b) : a;
}
void solve()
{
	scanf("%lld", &n);
	ll ans = 0, lcm = 1;
	for(ll i = 1; i; i++)
	{
		if(n <= 0)break;
		ll g = i / kpd(lcm, i);
		ans = (ans + (n - n / g) * i % mod) % mod;
		n /= g;
		lcm *= g;
	}
	printf("%lld\n", ans % mod);
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