#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 400;
int n, m;
int a[N][N];
int sum[N][N];
int res = 0;
int solve(int l, int r)
{
	int vis[N];
	int s[N], c[N], b[N];
	memset(vis, 0x3f, sizeof(vis));
	s[0] = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + sum[i][r] - sum[i][l - 1];
		c[i] = b[i] = s[i];
	}
	sort(c + 1, c + 1 + n);
	int cnt = unique(c + 1, c + 1 + n) - c - 1;
	for(int i = 1; i <= n; i++)
	{
		s[i] = lower_bound(c + 1, c + 1 + cnt, s[i]) - c;
		vis[s[i]] = min(vis[s[i]], i);
	}
	for(int i = 1; i <= n; i++)
		vis[i] = min(vis[i], vis[i - 1]);
	for(int i = 1; i <= n; i++)
	{
		if(vis[s[i]] <= i)
			ans = max(ans, i - vis[s[i]]);
		if(b[i] >= 0)
			ans = max(ans, i);
	}
	return ans;
}
signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			scanf("%lld", &a[i][j]);
			sum[i][j] = sum[i][j - 1] + a[i][j];
		}
	for(int i = 1; i <= m; i++)
		for(int j = 0; j + i <= m; j++)
			res = max(res, (j + 1) * solve(i, i + j));

	printf("%lld\n", res);
	return 0;
}
