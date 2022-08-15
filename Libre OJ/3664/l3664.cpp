#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, k;
struct State
{
	int a, b;
	bool operator < (const State &x)
	{
		return (~b && ~x.b) ? b < x.b : b>x.b;
	}
}p[N];
double f[N][N];
int tmp[N];
double get(int x)
{
	for(int i = 1; i <= n; i++)tmp[i] = p[i].a;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			f[i][j] = 1e9;
	f[0][0] = 0;
	double res = 1e9;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= min(x, i); j++)
		{
			f[i][j] = f[i - 1][j] + ((double)p[i].a / (x + 1));
			if(j >= 1 && p[i].b != -1)f[i][j] = min(f[i][j], f[i - 1][j - 1] + ((double)p[i].b / j));
		}
	}
	for(int i = k; i <= n; i++)
		res = min(res, f[i][x]);
	for(int i = k - 1; i >= x; i--)
	{
		sort(tmp + i + 1, tmp + n + 1);
		double val = 0;
		for(int j = 1; j <= k - i; j++)val += tmp[i + j];
		res = min(res, f[i][x] + ((double)val / (x + 1)));
	}
	return res;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].a, &p[i].b);
	sort(p + 1, p + 1 + n);
	double ans = 1e9;
	for(int i = 0; i <= k; i++)
		ans = min(ans, get(i));
	printf("%.15lf\n", ans);
	return 0;
}
