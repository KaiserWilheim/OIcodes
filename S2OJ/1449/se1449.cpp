#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
struct frac
{
	int p, q;
	frac() { p = 0, q = 0; }
	frac(int _p, int _q)
	{
		p = _p, q = _q;
	}
};
int n, m;
int t[N], a[N], b[N], d[N];
int f[N][N][2];
bool chq(frac mid)
{
	int p = mid.p, q = mid.q;
	memset(f, 0xc1, sizeof(f));
	f[0][0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		if(d[i] != 0)
		{
			for(int j = 0; j <= m; j++)
			{
				f[i][j][1] = max(f[i][j][1], f[i - 1][j][0] - d[i] * p);
				f[i][j][1] = max(f[i][j][1], f[i - 1][j][1] - d[i] * p);
			}
		}
		else
		{
			for(int j = 0; j <= m; j++)
			{
				f[i][j][0] = max(f[i][j][0], f[i - 1][j][0] - d[i] * p);
				f[i][j][1] = max(f[i][j][1], f[i - 1][j][1] - d[i] * p);
			}
		}
		if(b[i] != 0)
		{
			for(int j = t[i]; j <= m; j++)
			{
				f[i][j][1] = max(f[i][j][1], f[i - 1][j - t[i]][0] - b[i] * p + a[i] * q);
				f[i][j][1] = max(f[i][j][1], f[i - 1][j - t[i]][1] - b[i] * p + a[i] * q);
			}
		}
		else
		{
			for(int j = t[i]; j <= m; j++)
			{
				f[i][j][0] = max(f[i][j][0], f[i - 1][j - t[i]][0] - b[i] * p + a[i] * q);
				f[i][j][1] = max(f[i][j][1], f[i - 1][j - t[i]][1] - b[i] * p + a[i] * q);
			}
		}
	}
	for(int j = 0; j <= m; j++)
	{
		if(f[n][j][1] >= 0)return true;
		if(f[n][j][0] - p >= 0)return true;
	}
	return false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int c;
		scanf("%d%d%d%d%d", &t[i], &a[i], &b[i], &c, &d[i]);
		a[i] += c;
	}
	frac l(0, 1), r(1, 0);
	while(1)
	{
		frac mid(l.p + r.p, l.q + r.q);
		if(mid.p > 1000 || mid.q > 1000)break;
		if(chq(mid))l = mid;
		else r = mid;
	}
	printf("%d %d\n", l.p, l.q);
	return 0;
}