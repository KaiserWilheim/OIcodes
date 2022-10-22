#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
const ll mod = 1e9 + 7;
int n, m;
ll sum[N * 2], psum[N];
ll f[N][N];
int main()
{
	scanf("%d%d", &n, &m);
	m -= n;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			psum[j] = (psum[j] + sum[j]) % mod;
			if(j == 0)f[i][j] = 1;
			else f[i][j] = psum[j];
			sum[i + j] = (sum[i + j] + f[i][j]) % mod;
		}
	}
	printf("%lld\n", f[n][m]);
	return 0;
}