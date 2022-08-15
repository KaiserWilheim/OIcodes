#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll mod = 1e9 + 7;
int n;
ll a[N], b[N];
int main()
{
	scanf("%d", &n);
	ll ans = 1;
	a[0] = 1;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
		if (a[i] == 1)ans = (ans + b[i]) % mod;
	}
	int maxn = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1)continue;
		if ((ans + b[i]) * a[maxn] > (ans + b[maxn]) * a[i])maxn = i;
	}
	ans = (ans + b[maxn]) % mod;
	for (int i = 1; i <= n; i++)
	{
		if (i == maxn)continue;
		ans = (ans * a[i]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
