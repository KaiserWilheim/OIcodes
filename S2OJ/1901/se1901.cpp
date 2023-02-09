#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 32, M = 1010;
const int mod = 1e9 + 7;
int n, m, k;
int f[N][N][M][N];
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int lim = (1 << (k + 1)) - 1;
	f[1][0][0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int S = 0; S <= lim; S++)
			{
				for(int t = min(i - 1, k); t; t--)
				{
					f[i][j][S][t - 1] = add(f[i][j][S][t - 1], f[i][j][S][t]);
					if(i > t)f[i][j + 1][S ^ 1 ^ (1 << t)][t] = add(f[i][j + 1][S ^ 1 ^ (1 << t)][t], f[i][j][S][t]);
				}
				if((S & (1 << k)) == 0)f[i + 1][j][S << 1][min(i, k)] = add(f[i + 1][j][S << 1][min(i, k)], f[i][j][S][0]);
			}
		}
	}
	printf("%d\n", f[n][m][0][0]);
	return 0;
}
