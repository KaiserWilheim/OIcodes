#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N], cnt[N];
int dep;
ll dp[N][22];
ll res = 0;
int dl, dr;
ll calc(int l, int r)
{
	while(dl > l)res += cnt[a[--dl]]++;
	while(dr < r)res += cnt[a[++dr]]++;
	while(dl < l)res -= --cnt[a[dl++]];
	while(dr > r)res -= --cnt[a[dr--]];
	return res;
}
void solve(int l, int r, int ml, int mr)
{
	int mid = (l + r) >> 1;
	int pos = 0;
	int tl = max(1, ml), tr = min(mid, mr);
	ll minn = 1e15;
	for(int i = tl; i <= tr; i++)
	{
		ll val = dp[i - 1][dep - 1] + calc(i, mid);
		if(val < minn)minn = val, pos = i;
	}
	dp[mid][dep] = minn;
	if(l == r)return;
	solve(l, mid, ml, pos);
	solve(mid + 1, r, pos, mr);
}
int main()
{
	memset(dp, 127, sizeof(dp));
	dp[0][0] = 0;
	cnt[0] = 1;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	while(dep <= m)
	{
		dep++;
		solve(1, n, 1, n);
	}
	printf("%lld\n", dp[n][m]);
	return 0;
}