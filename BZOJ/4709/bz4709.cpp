#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n;
int col[N], cnt[N];
int s[N];
ll dp[N];
deque<int>sta[N];
ll calc(int p, int t)
{
	return dp[p - 1] + 1ll * col[p] * t * t;
}
int chq(int x, int y)
{
	int res = n + 1;
	int l = 1, r = n, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(calc(x, mid - s[x] + 1) >= calc(y, mid - s[y] + 1))
			res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}
#define sz(k) sta[k].size()
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		s[i] = ++cnt[col[i]];
	}
	for(int i = 1; i <= n; i++)
	{
		int t = col[i];
		while(sz(t) >= 2 && chq(sta[t][sz(t) - 2], sta[t][sz(t) - 1]) <= chq(sta[t][sz(t) - 1], i))
			sta[t].pop_back();
		sta[t].push_back(i);
		while(sz(t) >= 2 && chq(sta[t][sz(t) - 2], sta[t][sz(t) - 1]) <= s[i])
			sta[t].pop_back();
		dp[i] = calc(sta[t][sz(t) - 1], s[i] - s[sta[t][sz(t) - 1]] + 1);
	}
	printf("%lld\n", dp[n]);
	return 0;
}
