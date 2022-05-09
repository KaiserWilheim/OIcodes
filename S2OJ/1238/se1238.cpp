#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll n, m, q;
		scanf("%lld%lld%lld", &n, &m, &q);
		if((q < n) && (q < m))
		{//两个数都莫得用到
			printf("%lld\n", q);
			continue;
		}
		if(m > n)swap(m, n);
		if((q < n) && (q >= m))
		{//较大的数莫得用到
			printf("%lld\n", q - q / m);
			continue;
		}
		ll f[N];
		memset(f, -1, sizeof(f));
		ll tot = 0;
		f[0] = 0;
		while(1)
		{
			tot += n;
			ll x = tot % m;
			if(~f[x])break;
			f[x] = tot;
		}
		ll ans = (q - f[0]) / m;
		for(int i = 1; i < m; i++)
			if((~f[i]) && (q >= f[i]))
				ans += (q - f[i]) / m + 1;
		printf("%lld\n", q - ans);
	}
	return 0;
}
