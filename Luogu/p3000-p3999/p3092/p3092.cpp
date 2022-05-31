#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 1 << 17;
int m, n;
int tot;
int c[N], v[N];
int sum[N];
int dp[M], f[M];
int ans = 0x3f3f3f3f;
int chq(int x, int y)
{
	int l = y, r = m;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(sum[mid] - sum[y - 1] == x)return mid;
		if(sum[mid] - sum[y - 1] < x)l = mid + 1;
		else r = mid - 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
		tot += c[i];
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &v[i]);
		sum[i] = sum[i - 1] + v[i];
	}
	for(int S = 1; S < (1 << n); S++)
	{
		for(int i = 1; i <= n; i++)
		{
			if(S & (1 << (i - 1)))
			{
				int P = (S ^ (1 << (i - 1)));
				int x = chq(c[i], dp[P] + 1);
				if(x > dp[S])
				{
					dp[S] = x;
					f[S] = f[P] + c[i];
				}
				if(dp[S] == m)ans = min(f[S], ans);
			}
		}
	}
	printf("%d\n", (tot < ans) ? -1 : tot - ans);
	return 0;
}
