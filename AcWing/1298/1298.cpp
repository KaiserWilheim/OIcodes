#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll x, y, d;
int n;

void exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b)d = a, x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b)
{
	return a / gcd(a, b) * b;
}

ll a, b, A, B;

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		long long _a, _b;
		scanf("%lld%lld", &_a, &_b);
		A = _a, B = _b;
		if(i > 1)
		{
			exgcd(a, A, x, y);
			ll c = B - b;
			if(c % d)
			{
				puts("-1");
				return 0;
			}
			x = x * c / d % (A / d);
			if(x < 0)x += A / d;
			ll mod = lcm(a, A);
			b = (a * x + b) % mod;
			if(b < 0)b += mod;
			a = mod;
		}
		else
		{
			a = A, b = B;
		}
	}
	printf("%lld\n", ( ll )(b % a));
	return 0;
}
