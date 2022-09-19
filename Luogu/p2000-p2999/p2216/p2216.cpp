#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int a, b, n;
int h[N][N];
int f[N][N], g[N][N];
int main()
{
	scanf("%d%d%d", &a, &b, &n);
	for(int i = 1; i <= a; i++)
	{
		for(int j = 1; j <= b; j++)
		{
			scanf("%d", &h[i][j]);
			f[i][j] = g[i][j] = h[i][j];
		}
	}
	for(int k = 2; k <= n; k++)
	{
		for(int i = 1; i < a; i++)
		{
			for(int j = 1; j < b; j++)
			{
				f[i][j] = max(max(f[i][j], f[i + 1][j + 1]), max(f[i][j + 1], f[i + 1][j]));
				g[i][j] = min(min(g[i][j], g[i + 1][j + 1]), min(g[i][j + 1], g[i + 1][j]));
			}
		}
	}
	int ans = INT_MAX;
	for(int i = 1; i <= a - n + 1; i++)
		for(int j = 1; j <= b - n + 1; j++)
			ans = min(ans, f[i][j] - g[i][j]);
	printf("%d\n", ans);
	return 0;
}