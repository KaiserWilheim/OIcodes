#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	ll n, k, ans;
	scanf("%lld%lld", &n, &k);
	ans = n * k;
	for(int x = 1, gx; x <= n; x = gx + 1)
	{
		gx = (k / x) ? min(k / (k / x), n) : n;
		ans -= (k / x) * (x + gx) * (gx - x + 1) / 2;
	}
	printf("%lld\n", ans);
	return 0;
}
