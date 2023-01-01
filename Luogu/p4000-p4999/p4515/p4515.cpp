#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 32010;
int n;
ll ans;
struct tri
{
	ll x, y, r, c;
};
tri a[20];
void dfs(int p, ll x, ll y, ll c, int sz, int sign)
{
	if(x + y >= c)return;
	if(p == n + 1)
	{
		if(sz)ans += sign * (1ll << (sz - 1)) * (c - x - y) * (c - x - y);
	}
	else
	{
		dfs(p + 1, x, y, c, sz, sign);
		dfs(p + 1, max(x, a[p].x), max(y, a[p].y), min(c, a[p].c), sz + 1, -sign);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		ll x, y, r;
		scanf("%lld%lld%lld", &x, &y, &r);
		a[i] = { x,y,r,x + y + r };
	}
	dfs(1, 0, 0, 1e18, 0, -1);
	printf("%.1lf\n", ans / 2.0);
	return 0;
}
