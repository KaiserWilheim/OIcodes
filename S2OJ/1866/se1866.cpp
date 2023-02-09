#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010, M = N << 1;
int n, k, m, c, d;
int a[N];
int sum[N], cnt;
void add(int l, int r)
{
	l = max(l, 1ll), r = min(r, n);
	if(r < l)return;
	sum[l]++, sum[r + 1]--;
}
bool chq(int mid)
{
	cnt = 0;
	for(int i = 1; i <= n; i++)sum[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] >= mid)
		{
			cnt++;
			continue;
		}
		int x = a[i] + c;
		int num = m + 1;
		if(d)num = (mid - x + d - 1) / d;
		if(a[i] + c >= mid)num = 0;
		if(num >= min(m, i))continue;
		num = max(num, 0ll), num = min(num, m - 1);
		add(i - m + 1, i - num);
	}
	for(int i = 1; i <= n - m + 1; i++)
	{
		sum[i] += sum[i - 1];
		if(sum[i] + cnt >= k)return true;
	}
	return false;
}
signed main()
{
	scanf("%lld%lld%lld%lld%lld", &n, &k, &m, &c, &d);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	int l = 1, r = 1e18, ans = 0;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(chq(mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
