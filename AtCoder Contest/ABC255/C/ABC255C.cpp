#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
int main()
{
	ll x, a, d, n;
	scanf("%lld%lld%lld%lld", &x, &a, &d, &n);
	if(x == a)
	{
		puts("0");
		return 0;
	}
	if(d == 0)
	{
		printf("%lld\n", abs(x - a));
		return 0;
	}
	if(d < 0)
	{
		x = -x, d = -d, a = -a;
	}
	if(x < a)
	{
		printf("%lld\n", a - x);
		return 0;
	}
	ll to = (x - a) / d;
	if(to >= (n - 1))
	{
		printf("%lld\n", x - a - (n - 1) * d);
		return 0;
	}
	ll res = (x - a) % d;
	printf("%lld\n", min(res, d - res));
	return 0;
}
