#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n;
int a[N][N];
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	int res = 0;
	for(int k = 4; k <= n * 2; k += 4)
	{
		for(int i = 1 + (k > n); i <= n; i += 2)
		{
			int j = k - i;
			if(j > n || j < 1)continue;
			res ^= a[i][j];
			res ^= a[i][n - j + 1];
		}
	}
	printf("%d\n", res);
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
