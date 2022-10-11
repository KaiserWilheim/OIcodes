#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int n, c;
int h[N], sum[N], ssum[N];
int sta[N], tt;
int dp[N];
int calc(int l, int r, int maxn)
{
	int A = (r - l - 1),
		B = 2 * (sum[r - 1] - sum[l]),
		C = ssum[r - 1] - ssum[l];
	if(l >= 1)B += c, C += c * h[l];
	if(r <= n)B += c, C += c * h[r];
	int x = (B + A) / (2.0 * A);
	x = max(x, maxn);
	if(l >= 1)x = min(x, h[l]);
	if(r <= n)x = min(x, h[r]);
	return A * x * x - B * x + C;
}
signed main()
{
	scanf("%lld%lld", &n, &c);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &h[i]);
		sum[i] = sum[i - 1] + h[i];
		ssum[i] = ssum[i - 1] + h[i] * h[i];
	}
	h[0] = INT64_MAX, h[n + 1] = INT64_MAX - 1;
	sta[++tt] = 0;
	for(int i = 1; i <= n + 1; i++)
	{
		if(i == 1 || i == n + 1)dp[i] = dp[i - 1];
		else dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]) * c;
		while(h[i] >= h[sta[tt]])
		{
			tt--;
			dp[i] = min(dp[i], dp[sta[tt]] + calc(sta[tt], i, h[sta[tt + 1]]));
		}
		sta[++tt] = i;
	}
	printf("%lld\n", dp[n + 1]);
	return 0;
}