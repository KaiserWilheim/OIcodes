#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 110, M = 10010;
int k;
int a[N];
int f[N][M];
int dfs(int now, int sum, int p, bool lim)
{
	if(!now)return max(sum, 0ll);
	if(!lim && ~f[now][sum])return f[now][sum];
	int res = 0;
	int top = lim ? a[now] : k - 1;
	for(int i = 0; i <= top; i++)
		res += dfs(now - 1, sum + (p == 1 ? i * (now - 1) : (now < p ? -i : i)), p, lim && (i == top));
	if(!lim)f[now][sum] = res;
	return res;
}
int solve(int x)
{
	int n = 0;
	while(x)
	{
		a[++n] = x % k;
		x /= k;
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		memset(f, -1, sizeof(f));
		res += (i == 1 ? 1 : -1) * dfs(n, 0, i, 1);
	}
	return res;
}
signed main()
{
	int l, r;
	cin >> l >> r >> k;
	cout << solve(r) - solve(l - 1) << endl;
	return 0;
}
