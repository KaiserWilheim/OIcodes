#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
ll k;
ll loc[N], x[N];
ll a[N];
ll chg[N], tmp[N], ans[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &loc[i]);
		x[i] = loc[i] - loc[i - 1];
	}
	scanf("%d%lld", &m, &k);
	for(int i = 1; i <= m; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		chg[i] = i, ans[i] = i;
	for(int i = 1; i <= m; i++)
		swap(chg[a[i]], chg[a[i] + 1]);
	for(; k; k >>= 1)
	{
		if(k & 1)
		{
			for(int i = 1; i <= n; i++)tmp[i] = ans[chg[i]];
			for(int i = 1; i <= n; i++)ans[i] = tmp[i];
		}
		for(int i = 1; i <= n; i++)tmp[i] = chg[chg[i]];
		for(int i = 1; i <= n; i++)chg[i] = tmp[i];
	}
	for(int i = 1; i <= n; i++)tmp[i] = x[ans[i]];
	for(int i = 1; i <= n; i++)x[i] = tmp[i];
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		res += x[i];
		printf("%lld.0\n", res);
	}
	return 0;
}
