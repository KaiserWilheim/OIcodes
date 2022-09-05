#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 10010;
int n;
int dp[21][2521][51];
int arr[21];
map<int, int>dic;
int cnt;
int gcd(int a, int b)
{
	return !b ? a : gcd(b, a % b);
}
int _lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}
int dfs(int tot, int res, int lcm, bool lim)
{
	if(!tot)return (res % lcm == 0);
	if(!lim && dp[tot][res][dic[lcm]] != -1)return dp[tot][res][dic[lcm]];
	int top = lim ? arr[tot] : 9;
	int sum = 0;
	for(int i = 0; i <= top; i++)
		sum += dfs(tot - 1, (res * 10 + i) % 2520, (i == 0) ? lcm : _lcm(lcm, i), lim && (i == top));
	if(!lim)dp[tot][res][dic[lcm]] = sum;
	return sum;
}
int solve(int n)
{
	int tot = 0;
	while(n)
	{
		arr[++tot] = n % 10;
		n /= 10;
	}
	return dfs(tot, 0, 1, true);
}
signed main()
{
	for(int i = 1; i <= 2520; i++)
		if(2520 % i == 0)
			dic[i] = ++cnt;
	int T;
	cin >> T;
	memset(dp, -1, sizeof(dp));
	while(T--)
	{
		int l, r;
		cin >> l >> r;
		cout << solve(r) - solve(l - 1) << endl;
	}
	return 0;
}