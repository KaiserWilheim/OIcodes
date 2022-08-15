#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
ll n, m;
ll a[N], b[N];
ll calc(ll a, ll b)
{
	if (a % b == 0)return a / b;
	else return a / b + 1;
}
bool chq(ll k)
{
	__int128 tot = 0;
	for (int i = 1; i <= n; i++)
	{
		if (m * a[i] >= k)tot += m - calc(k, a[i]);
		else tot -= calc((k - m * a[i]), b[i]);
	}
	return tot >= 0;
}
int main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
		a[i] = max(a[i], b[i]);
	}
	ll l = 1, r = 1e18 + 10;
	ll ans;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (chq(mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
