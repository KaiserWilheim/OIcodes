#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
const ll mod = 998244353;
ll n, m;
ll calc(ll x, ll y)
{
	if(x == 0 || y == 0)return 0;
	ll res = 0, ans = 0;
	ll col = y / 2 + (y % 2 == 1);
	ll row = x / 2 + (x % 2 == 1);
	res = col * col % mod * row % mod;
	res = (res + row * (row - 1) % mod * m % mod * col % mod) % mod;
	ans = col * col % mod * (x - row) % mod;
	ans = (ans + (x - row) * (x - row) % mod * m % mod * col % mod) % mod;
	ans = (ans - (x - row) * y % mod * (y + 1) % mod * 499122177 % mod + mod) % mod;
	ans = (ans - m * y % mod * (x - row) % mod * (x - row) % mod + mod) % mod;
	return (res - ans + mod) % mod;
}
int main()
{
	scanf("%lld%lld", &n, &m);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		ll a, b, c, d;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		ll res = calc(b, d);
		res = (res - calc(a - 1, d) + mod) % mod;
		res = (res - calc(b, c - 1) + mod) % mod;
		res = (res + calc(a - 1, c - 1)) % mod;
		printf("%lld\n", res);
	}
	return 0;
}