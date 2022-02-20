#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000100;
int n, m, t, k;
int pos[MAXN], dp[MAXN << 2];
int ans;
inline void solve(int num)
{
	int res = 0;
	for(int i = 20; i >= 0; i--)
	{
		if(((k >> i) & 1) && ((num >> i) & 1)) dp[res + (1 << i)]++, dp[re + (1 << (i + 1))]--;
		else if((k >> i) & 1)
		{
			dp[res]++, dp[res + (1 << i)]--;
			res += (1 << i);
		}
		else if((num >> i) & 1)res += (1 << i);
	}
}
signed main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &pos[i]);
		solve(pos[i]);
	}
	for(int i = 0; i <= (1 << 20); i++)
	{
		if(i) dp[i] += dp[i - 1];
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
}
