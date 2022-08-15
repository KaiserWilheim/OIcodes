#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, k;
int a[N];
int chq(ll mid)
{
	int ans = 0;
	ll sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum = max(sum + a[i], 0ll);
		if (sum >= mid)sum = 0, ans++;
	}
	return ans;
}
ll l, r;
ll ans1 = -1, ans2 = -1;
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}

	l = 1, r = 1e18;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (chq(mid) <= k)
		{
			r = mid - 1;
			if (chq(mid) == k)ans1 = mid;
		}
		else l = mid + 1;
	}
	l = 1, r = 1e18;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (chq(mid) >= k)
		{
			l = mid + 1;
			if (chq(mid) == k)ans2 = mid;
		}
		else r = mid - 1;
	}
	if (ans1 == -1)puts("-1");
	else printf("%lld %lld\n", ans1, ans2);
	return 0;
}