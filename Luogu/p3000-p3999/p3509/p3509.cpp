#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
ll n, m, k;
ll a[N];
ll f[N][110];
ll ans[N];
int main()
{
	scanf("%lld%lld%lld", &n, &k, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	ll l = 1, r = k + 1;
	f[1][0] = k + 1;
	for(ll i = 2; i <= n; i++)
	{
		while(r + 1 <= n && a[i] - a[l] > a[r + 1] - a[i])l++, r++;
		if(a[i] - a[l] >= a[r] - a[i])f[i][0] = l;
		else f[i][0] = r;
	}
	for(int k = 1; k <= 60; k++)
		for(int i = 1; i <= n; i++)
			f[i][k] = f[f[i][k - 1]][k - 1];
	for(int i = 1; i <= n; i++)ans[i] = i;
	for(int k = 60; ~k; k--)
	{
		if((1ll << k) <= m)
		{
			for(int i = 1; i <= n; i++)
				ans[i] = f[ans[i]][k];
			m -= (1ll << k);
		}
		if(m == 0)break;
	}
	for(int i = 1; i <= n; i++)
		printf("%lld ", ans[i]);
	putchar('\n');
	return 0;
}