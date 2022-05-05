#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, k;
int hh, tt;
int f[N], q[N], sum[N];
int ans;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int v, w, c;
		scanf("%d%d%d", &w, &v, &c);
		if(v == 0)
		{
			ans += w * c;
			continue;
		}
		int x = k / v;
		c = min(c, x);
		for(int d = 0; d < v; d++)
		{
			hh = tt = 0;
			x = (k - d) / v;
			for(int j = 0; j <= x; j++)
			{
				while(hh < tt && f[d + j * v] - j * w >= q[tt - 1])tt--;
				sum[tt] = j;
				q[tt++] = f[d + j * v] - j * w;
				while(hh < tt && sum[hh] < j - c)hh++;
				f[d + j * v] = max(f[d + j * v], q[hh] + j * w);
			}
		}
	}
	printf("%d\n", ans + f[k]);
	return 0;
}
