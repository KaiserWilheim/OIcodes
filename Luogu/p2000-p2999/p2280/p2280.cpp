#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
int sum[N][N];
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		sum[x+1][y+1] += w;
		maxn = max(maxn, max(x+1, y+1));
	}
	for(int i = 2; i <= maxn; i++)
	{
		sum[i][1] += sum[i - 1][1];
		sum[1][i] += sum[1][i - 1];
	}
	for(int i = 2; i <= maxn; i++)
		for(int j = 2; j <= maxn; j++)
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	int ans = 0;
	for(int i = m; i <= maxn; i++)
		for(int j = m; j <= maxn; j++)
			ans = max(ans, sum[i][j] - sum[i - m][j] - sum[i][j - m] + sum[i - m][j - m]);
	cout << ans << endl;
	return 0;
}
