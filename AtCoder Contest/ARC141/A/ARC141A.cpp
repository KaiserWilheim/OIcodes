#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n10[22];
int main()
{
	n10[0] = 1;
	for(int i = 1; i <= 18; i++)
		n10[i] = n10[i - 1] * 10;
	int t;
	scanf("%d", &t);
	while(t--)
	{
		ll n;
		scanf("%lld", &n);
		int len = ceil(log10(n));
		ll ans = 11;
		for(int i = 2; i <= len && ans != n; i++)
		{
			if(len % i != 0)continue;
			ll tmp = n / n10[len / i * (i - 1)];
			ll res = 0;
			for(int j = 1; j <= i; j++)
				res = res * n10[len / i] + tmp;
			if(res <= n)ans = max(ans, res);
			tmp--;
			res = 0;
			for(int j = 1; j <= i; j++)
				res = res * n10[len / i] + tmp;
			if(res <= n)ans = max(ans, res);
		}
		ll res = 0;
		for(int i = 1; i < len; i++)
			res = res * 10 + 9;
		ans = max(res, ans);
		printf("%lld\n", ans);
	}
	return 0;
}
