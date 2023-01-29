#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010, M = N << 1;
int n, K;
int f[N][N][15], w[15];
int main()
{
	scanf("%d%d", &n, &K);
	memset(f, -63, sizeof(f));
	f[0][0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d", &p);
		for(int j = 1; j <= p; j++)
			scanf("%d", &w[j]);
		for(int j = K - 1; j >= 0; j--)
		{
			f[i][j][1] = f[i - 1][j][1];
			f[i][j][0] = f[i - 1][j][0];
			if(j + p <= K)
			{
				f[i][j + p][0] = max(f[i][j + p][0], f[i - 1][j][0] + w[p]);
				f[i][j + p][1] = max(f[i][j + p][1], f[i - 1][j][1] + w[p]);
			}
			for(int k = 1; k <= p && j + k <= K; k++)
				f[i][j + k][1] = max(f[i][j + k][1], f[i - 1][j][0] + w[k]);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= K; j++)
			ans = max(ans, f[i][j][0]);
		ans = max(ans, f[i][K][1]);
	}
	printf("%d\n", ans);
	return 0;
}
