#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
ll a, b;
ll gcd(ll a, ll b)
{
	if(a < b)swap(a, b);
	return b ? gcd(b, a % b) : a;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld", &a, &b);
		ll del = a * a - 4 * b * b;
		ll tmp = sqrt(del);
		if(tmp * tmp != del)
		{
			puts("0 0");
			continue;
		}
		ll x = a + tmp, y = 2 * b;
		ll g = gcd(x, y);
		printf("%lld %lld\n", x / g, y / g);
	}
	return 0;
}
