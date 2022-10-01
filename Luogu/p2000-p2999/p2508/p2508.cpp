#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
ll ans = 1;
int main()
{
	scanf("%lld", &n);
	for(ll i = 2; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			ll cnt = 0;
			while(n % i == 0)
			{
				cnt++;
				n /= i;
			}
			if(i % 4 == 1)ans *= (cnt * 2 + 1);
		}
	}
	if(n != 1 && n % 4 == 1)ans *= 3;
	printf("%lld\n", ans * 4);
	return 0;
}