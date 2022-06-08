#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 110;
const int mod = 1e9 + 7;
template<typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-')f = -1; c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
int n, m;
vector<int>e[N];
int dp[N][M][2][2];
int tmp[M][2][2];
int sz[N];
void dfs(int p, int fa)
{
	sz[p] = 1;
	dp[p][1][1][0] = dp[p][0][0][0] = 1;
	for(int q : e[p])
	{
		if(q == fa)continue;
		dfs(q, p);
		for(int i = 0; i <= min(sz[p], m); i++)
		{
			tmp[i][0][0] = dp[p][i][0][0]; dp[p][i][0][0] = 0;
			tmp[i][0][1] = dp[p][i][0][1]; dp[p][i][0][1] = 0;
			tmp[i][1][0] = dp[p][i][1][0]; dp[p][i][1][0] = 0;
			tmp[i][1][1] = dp[p][i][1][1]; dp[p][i][1][1] = 0;
		}
		for(int i = 0; i <= min(sz[p], m); i++)
		{
			for(int j = 0; j <= min(sz[q], m - i); j++)
			{
				dp[p][i + j][1][1] = (dp[p][i + j][1][1] + 1ll * tmp[i][1][1] * ((( ll )(dp[q][j][0][0] + dp[q][j][0][1]) + ( ll )(dp[q][j][1][0] + dp[q][j][1][1])) % mod)) % mod;
				dp[p][i + j][1][1] = (dp[p][i + j][1][1] + 1ll * tmp[i][1][0] * (dp[q][j][1][0] + dp[q][j][1][1])) % mod;
				dp[p][i + j][1][0] = (dp[p][i + j][1][0] + 1ll * tmp[i][1][0] * (dp[q][j][0][0] + dp[q][j][0][1])) % mod;
				dp[p][i + j][0][1] = (dp[p][i + j][0][1] + 1ll * tmp[i][0][1] * (dp[q][j][0][1] + dp[q][j][1][1])) % mod;
				dp[p][i + j][0][1] = (dp[p][i + j][0][1] + 1ll * tmp[i][0][0] * dp[q][j][1][1]) % mod;
				dp[p][i + j][0][0] = (dp[p][i + j][0][0] + 1ll * tmp[i][0][0] * dp[q][j][0][1]) % mod;
			}
		}
		sz[p] += sz[q];
	}
}
int main()
{
	n = read<int>(), m = read<int>();
	for(int i = 1; i < n; i++)
	{
		int u = read<int>(), v = read<int>();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	printf("%d\n", (dp[1][m][1][1] + dp[1][m][0][1]) % mod);
	return 0;
}
