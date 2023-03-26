#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(i) (i&-i)
const int N = 15, M = 510, K = (1 << 13) + 1;
int n, m;
int a[N], num[K];
ll f[K][N][M];
int main()
{
	scanf("%d%d", &n, &m);
	int U = (1 << n) - 1;
	a[0] = -1;
	int maxp = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(a[i] > a[maxp])maxp = i;
		num[1 << (i - 1)] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		int tmp = n * (a[maxp] - a[i] + (maxp < i));
		if(tmp <= m)f[1 << (i - 1)][i][tmp] = 1;
	}
	for(int S = 1; S < U; S++)
	{
		int popcnt = 0;
		for(int i = 1; i <= N; i++)
			if(S & (1 << (i - 1)))popcnt++;
		for(int T = S; T; T -= lowbit(T))
		{
			for(int sum = 0; sum <= m; sum++)
			{
				int pos = num[lowbit(T)];
				for(int i = 1; i <= n; i++)
				{
					if(S & (1 << (i - 1)))continue;
					int tmp = sum + (n - popcnt) * max(0, (pos < i) + a[pos] - a[i]);
					if(tmp <= m)f[S | (1 << (i - 1))][i][tmp] += f[S][pos][sum];
				}
			}
		}
	}
	ll ans = 0;
	for(int i = 0; i <= m; i++)
		for(int j = 1; j <= n; j++)
			ans += f[U][j][i];
	printf("%lld\n", ans);
	return 0;
}
