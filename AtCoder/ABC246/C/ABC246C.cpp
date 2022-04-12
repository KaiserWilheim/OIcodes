#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
ll p[N];
ll a;
int main()
{
	ll k, x;
	int n;
	scanf("%d%lld%lld", &n, &k, &x);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &p[i]);
		a += p[i] / x;
		p[i] %= x;
	}
	if(a >= k)
	{
		a -= k;
		k = 0;
	}
	else
	{
		k -= a;
		a = 0;
	}
	if(k > 0)
	{
		if(k > n)
		{
			puts("0");
			return 0;
		}
		sort(p + 1, p + 1 + n);
		for(int i = 1; i <= k; i++)p[n - i + 1] = 0;
	}
	ll ans = a * x;
	for(int i = 1; i <= n; i++)ans += p[i];
	printf("%lld\n", ans);
	return 0;
}
