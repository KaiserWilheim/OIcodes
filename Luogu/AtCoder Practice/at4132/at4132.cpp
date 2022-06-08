#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
template<typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-')f = -1; c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
int n;
char s[2];
int col[N << 1], num[N << 1];
int posb[N], posw[N];
ll dp[N][N], wb[N][N], ww[N][N];
int main()
{
	n = read<int>();
	for(int i = 1; i <= 2 * n; ++i)
	{
		scanf("%s", s);
		num[i] = read<int>();
		if(s[0] == 'B')col[i] = 1;
	}
	for(int i = 1; i <= 2 * n; ++i)
	{
		if(col[i] == 1)posb[num[i]] = i;
		else posw[num[i]] = i;
	}
	for(int i = 0; i < n; ++i)
	{
		for(int j = 1; j <= i; ++j)
		{
			ww[i][0] += (posw[j] > posw[i + 1]);
			wb[0][i] += (posb[j] > posb[i + 1]);
		}
	}
	for(int i = 0; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			wb[j][i] += wb[j - 1][i] + (posw[j] > posb[i + 1]);
			ww[i][j] += ww[i][j - 1] + (posb[j] > posw[i + 1]);
		}
	}
	for(int i = 0; i <= n; ++i)
	{
		for(int j = 0; j <= n; ++j)
		{
			dp[i][j] = 1e9 * (!(i == 0 && j == 0));
			if(i)dp[i][j] = min(dp[i - 1][j] + ww[i - 1][j], dp[i][j]);
			if(j)dp[i][j] = min(dp[i][j - 1] + wb[i][j - 1], dp[i][j]);
		}
	}
	printf("%lld", dp[n][n]);
	return 0;
}
