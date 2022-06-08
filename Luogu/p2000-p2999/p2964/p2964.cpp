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
int sum[N], c[N], dp[N][N];
int main()
{
	n = read<int>();
	for(int i = n; i >= 1; i--)
		c[i] = read<int>();
	for(int i = 1; i <= n; i++)
		sum[i] += sum[i - 1] + c[i];
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			dp[i][j] = dp[i][j - 1];
			int k = 2 * j - 1;
			if(k <= i)dp[i][j] = max(dp[i][j], sum[i] - dp[i - k][k]);
			k++;
			if(k <= i)dp[i][j] = max(dp[i][j], sum[i] - dp[i - k][k]);
		}
	}
	printf("%d\n", dp[n][1]);
	return 0;
}
