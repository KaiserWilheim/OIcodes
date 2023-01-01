#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 160, M = N << 1;
int n, m;
int a[N];
ll v[N];
ll f[N][N][N][2], g[N][N], h[N][N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &v[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memset(f, -63, sizeof(f));
	memset(g, -63, sizeof(g));
	for(int i = 0; i <= n; i++)
		g[i + 1][i] = 0;
	for(int l = n; l; l--)
	{
		f[l][l][1][0] = v[1];
		g[l][l] = v[1];
		for(int r = l + 1; r <= n; r++)
		{
			for(int mid = l; mid < r; mid++)
			{
				g[l][r] = max(g[l][mid] + g[mid + 1][r], g[l][r]);
				h[l][r] = max(h[l][mid] + h[mid + 1][r], h[l][r]);
			}
			for(int p = 1; p <= r - l + 1; p++)
			{
				for(int k = l; k < r; k++)
				{
					if(a[r] < a[k] && a[k] - a[r] == 1)
					{
						f[l][r][p][1] = max(f[l][r][p][1], f[l][k][p - 1][1] + g[k + 1][r - 1] + v[p] - v[p - 1]);
						f[l][r][p][1] = max(f[l][r][p][1], f[l][k][p - 1][0] + g[k + 1][r - 1] + v[p] - v[p - 1]);
					}
					else if(a[r] > a[k] && a[r] - a[k] == 1)
					{
						f[l][r][p][0] = max(f[l][r][p][0], f[l][k][p - 1][0] + g[k + 1][r - 1] + v[p] - v[p - 1]);
					}
				}
				g[l][r] = max(g[l][r], f[l][r][p][0]);
				g[l][r] = max(g[l][r], f[l][r][p][1]);
				h[l][r] = max(h[l][r], g[l][r]);
			}
		}
	}
	printf("%lld\n", h[1][n]);
	return 0;
}