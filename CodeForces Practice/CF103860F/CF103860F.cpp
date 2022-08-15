#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 22;
int n;
ll a[N];
ll ans;
void dfs(int p, ll x, bool flag)
{
	if(x <= ans)return;
	if(p > n)
	{
		if(flag)ans = x;
		return;
	}
	if(p == n && flag)
	{
		dfs(p + 1, x % a[p], flag | 1);
		return;
	}
	dfs(p + 1, x % a[p], flag | 1);
	dfs(p + 1, x, flag);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + 1 + n, greater<ll>());
	ll x;
	scanf("%lld", &x);
	dfs(1, x, 0);
	printf("%lld\n", ans);
	return 0;
}
