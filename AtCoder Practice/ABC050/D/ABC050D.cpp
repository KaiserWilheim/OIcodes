#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 1e9 + 7;
map<ll, ll>dic;
ll solve(ll x)
{
	if(dic.count(x))return dic[x];
	dic[x] = (solve(x / 2) + solve((x - 1) / 2) + solve((x - 2) / 2)) % mod;
	return dic[x];
}
int main()
{
	dic[0] = 1;
	dic[1] = 2;
	ll n;
	scanf("%lld", &n);
	ll ans = solve(n);
	printf("%lld\n", ans);
	return 0;
}