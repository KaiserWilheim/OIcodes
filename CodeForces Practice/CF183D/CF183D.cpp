#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010, M = 310;
int n, m;
double p[N][M], f[M][N];
double del[N], sv[N], siv[N], val[N];
int cnt[M];
void calc(int c)
{
	double g[N] = {};
	memcpy(g, f[c], sizeof(g));
	f[c][0] = 0;
	for(int i = 1; i <= n; i++)
		f[c][i] = f[c][i - 1] * (1 - p[i][c]) + g[i - 1] * p[i][c];
	cnt[c]++;
	siv[c] += cnt[c] * f[c][n];
	sv[c] += f[c][n];
	double res = siv[c] + cnt[c] * (1 - sv[c]);
	del[c] = res - val[c];
	val[c] = res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int x;
			scanf("%d", &x);
			p[i][j] = x / 1000.0;
		}
	}
	for(int i = 1; i <= m; i++)
	{
		f[i][0] = 1;
		for(int j = 1; j <= n; j++)
			f[i][j] = f[i][j - 1] * (1 - p[j][i]);
		sv[i] = f[i][n];
		calc(i);
	}
	double ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int maxn = 0;
		for(int j = 1; j <= m; j++)
			if(del[maxn] < del[j])maxn = j;
		if(!maxn)break;
		ans += del[maxn];
		calc(maxn);
	}
	printf("%.12lf\n", ans);
	return 0;
}
