#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = 65;
const ll mod = 1e9 + 7;
int n;
int m;
int a[N];
int qpow[N];
ll dp[N][M][M][2];
ll dfs(int now, int sum, int ret, bool lim)
{
	if(now > n)return (ret == 0) ? 1 : 0;
	if(~dp[now][sum][ret][lim])return dp[now][sum][ret][lim];
	ll res = 0;
	int top = (lim ? a[now] : 9);
	for(int i = 0; i <= top; i++)
		res = (res + dfs(now + 1, (i + sum) % m, ((ret + i * sum - i * qpow[n - now]) % m + m) % m, i == top && lim)) % mod;
	dp[now][sum][ret][lim] = res;
	return res;
}
ll calc(char *s, int del)
{
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		a[i] = s[i] - '0';
	a[n] -= del;
	for(int i = n; i > 1; i--)
	{
		if(a[i] < 0)
		{
			a[i - 1]--;
			a[i] += 10;
		}
		else break;
	}
	if(a[1] == 0)
	{
		for(int i = 1; i < n; i++)
			a[i] = a[i + 1];
		n--;
	}
	qpow[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		qpow[i] = qpow[i - 1] * 10 % m;
		memset(dp[i], -1, sizeof(dp[i]));
	}
	return dfs(1, 0, 0, 1);
}
char l[N], r[N];
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%s", l + 1);
		scanf("%s", r + 1);
		scanf("%d", &m);
		ll res = calc(r, 0) - calc(l, 1);
		res = (res % mod + mod) % mod;
		printf("%lld\n", res);
	}
	return 0;
}
