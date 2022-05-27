#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll n;
	while(scanf("%lld", &n) == 1)
	{
		ll ans = 1, res = 1;
		while(res != 0)
		{
			res = (res * 10 + 1) % n;
			ans++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
