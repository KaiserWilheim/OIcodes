#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 24, M = (1 << 23) + 10;
int n, m, K;
int g[N][N], w[N][N], c[N][N];
int sz[M], lg[M];
int f[M];
int main()
{
	scanf("%d%d%d", &n, &m, &K);
	int u = 0, v;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &v);
		if(u)g[u][v]++;
		u = v;
	}
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(i == j)continue;
			w[0][i] += g[j][i] * K - g[i][j];
			c[i][j] = g[i][j] * (1 + K) + g[j][i] * (1 - K);
		}
	}
	int U = (1 << m) - 1;
	for(int i = 1; i <= U; i++)
		sz[i] = sz[i >> 1] + (i & 1), lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= U; i++)f[i] = 1e9;
	for(int i = 0; i < U; i++)
	{
		int z = lg[i & -i];
		if(sz[i])
			for(int j = 1; j <= m; j++)
				w[sz[i]][j] = w[sz[i] - 1][j] + c[j][z];
		int x, y;
		for(x = U ^ i; y = x & -x; x ^= y)
			z = f[i] + w[sz[i]][lg[y]] * (sz[i] + 1), f[i | y] = min(f[i | y], z);
	}
	printf("%d\n", f[U]);
	return 0;
}
