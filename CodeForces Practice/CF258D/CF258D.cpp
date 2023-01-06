#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = N << 1;
int n, m;
int a[N];
double f[N][N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = (a[i] > a[j]) ? 1 : 0;
	while(m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		for(int i = 1; i <= n; i++)
		{
			f[x][i] = f[y][i] = 0.5 * (f[x][i] + f[y][i]);
			f[i][x] = f[i][y] = 1.0 - f[x][i];
		}
		f[x][y] = f[y][x] = 0.5;
	}
	double res = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			res += f[i][j];
	printf("%.9lf\n", res);
	return 0;
}
