#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
bool ispow(ll n)
{
	return ((n & (n - 1)) == 0);
}
ll f(ll n)
{
	int dep = ceil(log2(n));
	if(ispow(n) || (ispow(n - 1)))return 2 * n - 1;
	return f(n >> 1) + (1ll << dep);
}
ll fx(ll n)
{
	if(n == 0)return 0ll;
	ll res = 0;
	map<ll, bool>m;
	for(ll i = 1; i <= n; i <<= 1)
	{
		if(i <= n && !m[i])
		{
			m[i] = true;
			res ^= f(i);
		}
		if(i + 1 <= n && !m[i + 1])
		{
			m[i + 1] = true;
			res ^= f(i + 1);
		}
	}
	if((n & 1) == 0 && !m[n])res ^= f(n);
	return res;
}
int main()
{
	ll l, r;
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", fx(r) ^ fx(l - 1));
	return 0;
}
