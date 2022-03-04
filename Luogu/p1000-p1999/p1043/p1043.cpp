#include <bits/stdc++.h>
using namespace std;
const int N = 110;
const int INF = 0x3f3f3f3f;
const int n9[9] = { 9,81,729,6561,59409,531441,4782969,43046721,387420489 };
int n, m;
int a[N];
int minn = INF, maxn = 0;
int mod10(int x)
{
	return (x % 10 + 10) % 10;
}
void dfs(int depth, int now, int val)
{
	if(val >= minn && val * n9[m - depth] <= maxn) return;
	int sum = 0;
	if(depth == m)
	{
		for(int i = now; i <= n; i++) sum += a[i];
		minn = min(minn, val * mod10(sum));
		maxn = max(maxn, val * mod10(sum));
		return;
	}
	for(int i = now; i <= (n - m + depth); i++)
	{
		sum += a[i];
		dfs(depth + 1, i + 1, val * mod10(sum));
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i + n] = a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		dfs(1, 1, 1);
		for(int j = 1; j <= 2 * n; j++) a[j] = a[j + 1];
	}
	printf("%d\n%d\n", minn, maxn);
	return 0;
}
