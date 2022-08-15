#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n;
ll f[2][N];
ll ans = 1e18;
int a[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memset(f, 63, sizeof(f));
	f[0][1] = a[n];
	for(int i = 1; i < n; i++)
	{
		f[1][i + 1] = min(f[1][i + 1], min(f[0][i], f[1][i]) + a[i + 1]);
		f[0][i + 1] = f[1][i];
	}
	ans = min(ans, min(f[0][n - 1], f[1][n - 1]));
	memset(f, 63, sizeof(f));
	f[1][1] = a[1];
	for(int i = 1; i <= n; i++)
	{
		f[1][i + 1] = min(f[1][i + 1], min(f[0][i], f[1][i]) + a[i + 1]);
		f[0][i + 1] = f[1][i];
	}
	ans = min(ans, min(f[0][n], f[1][n]));
	printf("%lld\n", ans);
	return 0;
}
