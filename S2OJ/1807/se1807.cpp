#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, k;
int a[N];
int sum, ans;
void dfs1(int p, int fa, int dep)
{
	if((k - dep + 1) & 1)sum ^= a[p];
	if(dep < k)dfs1(p << 1, p, dep + 1);
	if(dep < k)dfs1(p << 1 | 1, p, dep + 1);
}
void dfs2(int p, int fa, int dep)
{
	if((k - dep + 1) & 1)
	{
		int tmp = sum ^ a[p];
		if(a[p] > tmp)
		{
			if(k != dep)ans += 2;
			else ans++;
		}
		if(fa && a[p] < tmp && tmp <= a[p] + a[fa])ans++;
	}
	if(dep < k)dfs2(p << 1, p, dep + 1);
	if(dep < k)dfs2(p << 1 | 1, p, dep + 1);
}
void solve()
{
	scanf("%d", &k);
	n = (1 << k) - 1;
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dfs1(1, 0, 1);
	dfs2(1, 0, 1);
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ans = sum = 0;
		solve();
	}
	return 0;
}