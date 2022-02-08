#include<bits/stdc++.h>
using namespace std;
long long gcd(long long x, long long y)
{
	if(y == 0)return x;
	return gcd(y, x % y);
}
int main()
{
	int T;
	long long a, b, c;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld%lld", &a, &b, &c);
		if(a == 0)b = 1;
		b /= gcd(a, b);
		long long g = gcd(b, c);
		while(g != 1)
		{
			while(b % g == 0)b /= g;
			g = gcd(b, c);
		}
		if(b == 1)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
