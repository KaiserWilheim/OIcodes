#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
const ll mod = 9999973;
int n, m;
ll ans;
ll f[N][N][N];
//f[第几行][有几列是只有一个棋子的][有几列是有两个棋子的]
ll C(int x)
{
	return ((x * (x - 1ll)) / 2ll) % mod;
}

int main()
{
	scanf("%d%d", &n, &m);
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = 0; k <= m; k++)
			{
				f[i][j][k] = f[i - 1][j][k];
				if(k >= 1)f[i][j][k] += f[i - 1][j + 1][k - 1] * (j + 1);//1->2
				if(j >= 1)f[i][j][k] += f[i - 1][j - 1][k] * (m - j - k + 1);//0->1
				if(k >= 2)f[i][j][k] += f[i - 1][j + 2][k - 2] * C(j + 2);//1=>2
				if(j >= 2)f[i][j][k] += f[i - 1][j - 2][k] * C(m - j - k + 2);//0=>1
				if(k >= 1)f[i][j][k] += f[i - 1][j][k - 1] * j * (m - j - k + 1);//0->1->2
				f[i][j][k] %= mod;
			}
		}
	}
	for(int i = 0; i <= m; i++)
		for(int j = 0; j <= m; j++)
			ans = (ans + f[n][i][j]) % mod;
	printf("%lld\n", ans);
	return 0;
}
