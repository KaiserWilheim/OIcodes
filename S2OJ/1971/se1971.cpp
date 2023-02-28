#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
const double eps = 1e-6;
int n, m, c;
double p, q;
double f[N][N];
bool chq(double x)
{
	for(int i = 1; i <= m; i++)f[0][i] = x;
	for(int i = 1; i <= n; i++)f[i][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(i == n && j == m)
			{
				f[i][j] = 1 + p * f[i][j - 1] + q * f[i - 1][j];
				return f[i][j] <= x;
			}
			else f[i][j] = min(x, 1 + p * f[i][j - 1] + q * f[i - 1][j]);
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &c);
	p = c / 100.0, q = (100 - c) / 100.0;
	double l = 1, r = 1e9, mid;
	if(!chq(r))
	{
		printf("%.9lf\n", r);
		return 0;
	}
	while(r - l > eps)
	{
		mid = (l + r) / 2.0;
		if(chq(mid))r = mid;
		else l = mid;
	}
	printf("%.9lf\n", mid);
	return 0;
}
