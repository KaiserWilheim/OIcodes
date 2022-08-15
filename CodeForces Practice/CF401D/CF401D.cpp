#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int a[20];
bool vis[20];
ll dp[N][110];
int cnt = -1;
int main()
{
	ll n;
	int m;
	scanf("%lld%d", &n, &m);
	while(n)
	{
		a[++cnt] = n % 10;
		n /= 10;
	}
	dp[0][0] = 1;
	for(int S = 1; S < 1 << (cnt + 1); S++)
	{
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i <= cnt; i++)
		{
			if(S == (1 << i) && !a[i]) break;
			if(!(S & (1 << i)) || vis[a[i]]) continue;
			vis[a[i]] = 1;
			for(int j = 0; j < m; j++)
				dp[S][(j * 10 + a[i]) % m] = (dp[S][(j * 10 + a[i]) % m] + dp[S ^ (1 << i)][j]);
		}
	}
	printf("%lld\n", dp[(1 << (cnt + 1)) - 1][0]);
	return 0;
}
