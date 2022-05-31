#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, M = 100010;
int n, m;
int f[N];
int s[M][30];
int num[30], sum[N];
void dfs(int x, int S, bool flag)
{
	if(x == m)return;
	if(flag)
	{
		sum[S | (1 << x)] = sum[S] + num[x + 1];
		dfs(x + 1, S | (1 << x), 1);
		dfs(x + 1, S | (1 << x), 0);
	}
	else
	{
		dfs(x + 1, S, 1);
		dfs(x + 1, S, 0);
	}
}
int main()
{

	scanf("%d%d", &n, &m);
	for(int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		for(int j = 1; j <= m; j++)
			s[i][j] = s[i - 1][j];
		s[i][x]++;
		num[x]++;
	}
	dfs(0, 0, 0);
	dfs(0, 0, 1);
	memset(f, 63, sizeof(f));
	f[0] = 0;
	for(int S = 1; S < (1 << m); S++)
	{
		for(int i = 1; i <= m; i++)
			if(S & (1 << (i - 1)))
			{
				int l = sum[S ^ (1 << (i - 1))], r = sum[S];
				f[S] = min(f[S], f[S ^ (1 << (i - 1))] + (r - l) - (s[r][i] - s[l][i]));
			}
	}
	printf("%d\n", f[(1 << m) - 1]);
	return 0;
}
