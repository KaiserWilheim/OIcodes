#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e9;
ll n, k;
int main()
{
	scanf("%lld%lld", &n, &k);
	ll res = 0;
	if(k >= n)
	{
		res = n * (n - 1) / 2;
	}
	else
	{
		ll x = n / k, y = n % k;
		res = x * (k * (k - 1) / 2) + (y * (y - 1) / 2);
		res += x * (x - 1) * (k * (k - 1) / 2);
		res += x * ((y * (y + 1) / 2) + (k - y - 1) * y);
		res += x * (y * (y - 1) / 2);
	}
	printf("%lld\n", res);
	return 0;
}