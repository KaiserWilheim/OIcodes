#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
const ll mod = 998244353;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n;
ll f[N][N][N];
int a[N];
pair<int, int>tmp[N];
ll solve(int l, int r, int lim)
{
	if(f[l][r][lim])return f[l][r][lim];
	int maxn = 0;
	for(int i = l; i <= r; i++)
		if(a[i] <= lim)maxn = max(maxn, a[i]);
	if(maxn == 0)return f[l][r][lim] = 1;
	ll res = 0;
	bool flag = false;
	for(int i = l; i <= r; i++)
	{
		if(a[i] == maxn)flag = true;
		if(flag && a[i] <= lim)
			res = add(res, solve(l, i, maxn - 1) * solve(i + 1, r, maxn - 1) % mod);
	}
	return f[l][r][lim] = res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = make_pair(a[i], i);
	}
	sort(tmp + 1, tmp + 1 + n);
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(tmp + 1, tmp + 1 + n, make_pair(a[i], i)) - tmp;
	printf("%lld\n", solve(1, n, n));
	return 0;
}
