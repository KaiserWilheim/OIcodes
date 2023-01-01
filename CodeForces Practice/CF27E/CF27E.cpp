#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = N << 1;
int n;
ll p[20] = { 0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 };
ll ans = 1e18;
void dfs(ll now, int k, int last, int cnt)
{
	if(cnt > n)return;
	if(now > ans)return;
	if(k > 16)return;
	if(cnt == n)
	{
		ans = now;
		return;
	}
	for(int i = 1; i <= last; i++)
	{
		if(INT64_MAX / p[k] < now)continue;
		dfs(now *= p[k], k + 1, i, cnt * (i + 1));
	}
}
int main()
{
	scanf("%d", &n);
	dfs(1, 1, 64, 1);
	printf("%lld\n", ans);
	return 0;
}
