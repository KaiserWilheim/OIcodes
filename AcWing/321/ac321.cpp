#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20, M = 10;
int n, m = 8;
int s[M][M];
double f[M][M][M][M][N];
double X;
double get(int x1, int y1, int x2, int y2)
{
	double delta = s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
	delta = delta - X;
	return delta * delta;
}
double dp(int x1, int y1, int x2, int y2, int k)
{
	if(f[x1][y1][x2][y2][k] >= 0)return f[x1][y1][x2][y2][k];
	if(k == n)return f[x1][y1][x2][y2][k] = get(x1, y1, x2, y2);
	double t = 1e9;
	for(int i = x1; i < x2; i++)
	{
		t = min(t, dp(x1, y1, i, y2, k + 1) + get(i + 1, y1, x2, y2));
		t = min(t, dp(i + 1, y1, x2, y2, k + 1) + get(x1, y1, i, y2));
	}
	for(int i = y1; i < y2; i++)
	{
		t = min(t, dp(x1, y1, x2, i, k + 1) + get(x1, i + 1, x2, y2));
		t = min(t, dp(x1, i + 1, x2, y2, k + 1) + get(x1, y1, x2, i));
	}
	return f[x1][y1][x2][y2][k] = t;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &s[i][j]);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	memset(f, -1, sizeof(f));
	X = ( double )s[m][m] / n;
	printf("%.3lf\n", sqrt(dp(1, 1, m, m, 1) / n));
	return 0;
}
