#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 160, M = 20;
ll l, r;
int a[M], len;
ll mod;
ll dp[M][N][N];
ll dfs(int pos, int sum, ll now, bool lim)
{
	if(pos > len)return (now == 0 && sum == mod) ? 1 : 0;
	if(!lim && dp[pos][sum][now] != -1)return dp[pos][sum][now];
	ll res = 0;
	int top = lim ? a[len - pos + 1] : 9;
	for(int i = 0; i <= top; i++)
		res += dfs(pos + 1, sum + i, (10 * now + i) % mod, i == top && lim);
	dp[pos][sum][now] = res;
	return res;
}
ll calc(ll x)
{
	len = 0;
	while(x)
	{
		a[++len] = x % 10;
		x /= 10;
	}
	ll res = 0;
	for(mod = 1; mod <= 9 * len; mod++)
	{
		memset(dp, -1, sizeof(dp));
		res += dfs(1, 0, 0, true);
	}
	return res;
}
int main()
{
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", calc(r) - calc(l - 1));
	return 0;
}