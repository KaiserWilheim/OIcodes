#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, ans;
int f[1 << 10][1 << 10][3], a[105], sum[1 << 10];

int main()
{
	scanf("%d%d", &n, &m);
	if((n == 1) && (m == 1))
	{
		char x;
		cin >> x;
		x == 'P' ? puts("1") : puts("0");
		return 0;
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			char x;
			cin >> x;
			a[i] <<= 1;
			a[i] += (x == 'H') ? 1 : 0;
		}
	}

	for(int i = 0; i < (1 << m); i++)sum[i] = __builtin_popcount(i);
	for(int i = 0; i < (i << m); i++)
		if(!((i & a[0]) || (i & (i << 1)) || (i & (i << 2))))
			f[0][i][0] = sum[i];
	for(int i = 0; i < (1 << m); i++)
		for(int j = 0; j < (1 << m); j++)
			if((i & j) || (i & a[0]) || (j & a[1]) || (i & (i << 1)) || (i & (i << 2)) || (j & (j << 1)) || (j & (j << 2)))continue;
			else f[i][j][1] = sum[i] + sum[j];
	for(int i = 2; i < n; i++)
		for(int l = 0; l < (1 << m); l++)
			if(l & a[i - 1] || (l & (l << 1)) || (l & (l << 2))) continue;
			else for(int s = 0; s < (1 << m); s++)
				if(s & a[i] || l & s || (s & (s << 1)) || (s & (s << 2))) continue;
				else for(int j = 0; j < (1 << m); j++)
					if(j & l || j & s || j & a[i - 2] || (j & (j << 1)) || (j & (j << 2)))	continue;
					else f[l][s][i % 3] = max(f[l][s][i % 3], f[j][l][(i - 1) % 3] + sum[s]);

	for(int l = 0; l < (1 << m); l++)
		for(int s = 0; s < (1 << m); s++)
			ans = max(ans, f[l][s][(n - 1) % 3]);
	printf("%d\n", ans);
	return 0;
}
