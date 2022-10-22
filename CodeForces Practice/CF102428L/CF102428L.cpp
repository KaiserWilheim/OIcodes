#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, m;
char s[N][N];
int sum[N][N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		cin >> s[i] + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 2; j <= m; j++)
		{
			if(s[i][j] != s[i][j - 1])
				sum[i][j] = 1;
			sum[i][j] += sum[i][j - 1];
		}
	}
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			for(int k = max(1, maxn); k <= min(i, j); k++)
			{
				bool flag = true;
				for(int l = i - k + 1; l <= i; l++)
				{
					if(sum[l][j] - sum[l][j - k + 1] > 0)
					{
						flag = false;
						break;
					}
				}
				if(flag)maxn = max(maxn, k);
			}
		}
	}
	printf("%d\n", maxn * maxn);
	return 0;
}