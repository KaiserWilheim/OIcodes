#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll dp[15], sum[15], mi[15];
ll ans1[15], ans2[15];
int now[15];
inline void solve(ll n, ll *ans)
{
	ll res = n;
	int len = 0;
	while(n) now[++len] = n % 10, n /= 10;
	for(int i = len; i >= 1; i--)
	{
		for(int j = 0; j < 10; j++)
		{
			ans[j] += dp[i - 1] * now[i];
		}
		for(int j = 0; j < now[i]; j++)
		{
			ans[j] += mi[i - 1];
		}
		res -= mi[i - 1] * now[i];
		ans[now[i]] += res + 1;
		ans[0] -= mi[i - 1];
	}
}
int main()
{
	ll a, b;
	scanf("%lld%lld", &a, &b);
	mi[0] = 1ll;
	for(int i = 1; i <= 13; ++i)
	{
		dp[i] = dp[i - 1] * 10 + mi[i - 1];
		mi[i] = 10ll * mi[i - 1];
	}
	solve(b, ans1);
	solve(a - 1, ans2);
	for(int i = 0; i <= 9; i++)
	{
		printf("%lld", ans1[i] - ans2[i]);
		i == 9 ? putchar('\n') : putchar(' ');
	}
	return 0;
}
