#include <bits/stdc++.h>
using namespace std;
const int N = 3010;
int n;
int a[N], b[N];
int f[N][N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++)
	{
		int val = 1;
		for(int j = 1; j <= n; j++)
		{
			if(a[i] == b[j])f[i][j] = val;
			else f[i][j] = f[i - 1][j];
			if(b[j] < a[i])val = max(val, f[i - 1][j] + 1);
		}
	}
	int maxn = 0;
	for(int i = 1; i <= n; i++)
		maxn = max(maxn, f[n][i]);
	printf("%d\n", maxn);
	return 0;
}
