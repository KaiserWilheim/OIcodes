#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n;
int a[N];
int f[N][N];
int rt[N][N];
void dfs(int l, int r)
{
	if(l > r)return;
	printf("%d ", rt[l][r]);
	dfs(l, rt[l][r] - 1);
	dfs(rt[l][r] + 1, r);
	return;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int len = 1; len <= n; len++)
	{
		for(int l = 1; l + len - 1 <= n; l++)
		{
			int r = l + len - 1;
			for(int k = l; k <= r; k++)
			{
				int ls = (k == l) ? 1 : f[l][k - 1];
				int rs = (k == r) ? 1 : f[k + 1][r];
				int res = ls * rs + a[k];
				if(l == r)res = a[k];
				if(res > f[l][r])
				{
					f[l][r] = res;
					rt[l][r] = k;
				}
			}
		}
	}
	printf("%d\n", f[1][n]);
	dfs(1, n);
	putchar('\n');
	return 0;
}
