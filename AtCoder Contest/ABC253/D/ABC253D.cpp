#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	ll n, a, b;
	scanf("%lld%lld%lld", &n, &a, &b);
	ll ans = (n + 1) * n / 2;
	ll g = a * b / gcd(a, b);
	ll da = n / a;
	ans -= a * ((da + 1) * da / 2);
	ll db = n / b;
	ans -= b * ((db + 1) * db / 2);
	ll dg = n / g;
	ans += g * ((dg + 1) * dg / 2);
	printf("%lld\n", ans);
	return 0;
}
