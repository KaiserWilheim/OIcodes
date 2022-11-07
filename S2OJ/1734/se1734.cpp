#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 260;
int n, m;
char s[N][N];
int a[N][N], sum[N][N];
int f[2][N][N][N], g[2][N][N][N];
bool chq(int l, int t, int r, int b)
{
	int k = sum[r][b] - sum[l - 1][b] - sum[r][t - 1] + sum[l - 1][t - 1];
	return (k == 0) || (k == (r - l + 1) * (b - t + 1));
}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> s[i] + 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			a[i][j] = (s[i][j] == '.');
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	for(int i = 1; i <= m; i++)
	{
		for(int l = 1; l <= n; l++)
		{
			int now = m;
			for(int r = l; r <= n; r++)
			{
				while(now >= i && !chq(l, i, r, now))now--;
				f[0][i][l][r] = now;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int l = 1; l <= m; l++)
		{
			int now = n;
			for(int r = l; r <= m; r++)
			{
				while(now >= i && !chq(i, l, now, r))now--;
				g[0][i][l][r] = now;
			}
		}
	}
	if(f[0][1][1][n] == m)
	{
		puts("0");
		return 0;
	}
	for(int ans = 1, k = 1;; ans++, k ^= 1)
	{
		memset(f[k], 0, sizeof(f[k]));
		memset(g[k], 0, sizeof(g[k]));
		for(int i = 1; i <= m; i++)
		{
			for(int l = 1; l <= n; l++)
			{
				int now = m;
				for(int r = l; r <= n; r++)
				{
					if(f[!k][i][l][r] < m)f[k][i][l][r] = f[!k][f[!k][i][l][r] + 1][l][r];
					else f[k][i][l][r] = m;
					while(now >= i && g[!k][l][i][now] < n && g[!k][g[!k][l][i][now] + 1][i][now] < r)now--;
					f[k][i][l][r] = max(f[k][i][l][r], now);
				}
			}
		}
		for(int i = 1; i <= n; i++)
		{
			for(int l = 1; l <= m; l++)
			{
				int now = n;
				for(int r = l; r <= m; r++)
				{
					if(g[!k][i][l][r] < n)g[k][i][l][r] = g[!k][g[!k][i][l][r] + 1][l][r];
					else g[k][i][l][r] = n;
					while(now >= i && f[!k][l][i][now] < m && f[!k][f[!k][l][i][now] + 1][i][now] < r)now--;
					g[k][i][l][r] = max(g[k][i][l][r], now);
				}
			}
		}
		if(f[k][1][1][n] == m)
		{
			printf("%d\n", ans);
			return 0;
		}
	}
	return 0;
}