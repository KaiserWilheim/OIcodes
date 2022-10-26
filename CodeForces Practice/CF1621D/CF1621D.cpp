#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, m;
ll a[N][N];
void solve()
{
	scanf("%d", &n);
	m = n * 2;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	ll res = 0;
	for(int i = n + 1; i <= m; i++)
		for(int j = n + 1; j <= m; j++)
			res += a[i][j], a[i][j] = 0;
	ll ans = min(min(a[n + 1][n], a[n][n + 1]), min(a[n][m], a[m][n]));
	ans = min(ans, min(min(a[1][m], a[m][1]), min(a[1][n + 1], a[n + 1][1])));
	printf("%lld\n", res + ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}