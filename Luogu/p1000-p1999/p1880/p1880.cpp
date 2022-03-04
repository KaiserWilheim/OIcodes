#include<bits/stdc++.h>
using namespace std;
int n;
int a[220], sum[220];
int fa[220][220], fi[220][220];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i + n] = a[i];
	}
	for(int i = 1; i <= n * 2; i++)
	{
		sum[i] = sum[i - 1] + a[i];
	}
	for(int len = 1; len <= n; len++)
	{
		for(int i = 1; i <= 2 * n - 1; i++)
		{
			int j = len + i;
			fi[i][j] = 99999999;
			for(int k = i; k < j && k <= 2 * n - 1; k++)
			{
				fa[i][j] = max(fa[i][j], fa[i][k] + fa[k + 1][j] + sum[j] - sum[i - 1]);
				fi[i][j] = min(fi[i][j], fi[i][k] + fi[k + 1][j] + sum[j] - sum[i - 1]);
			}
		}
	}
	int maxn = -1, minn = 99999999;
	for(int i = 1; i <= n; i++)
	{
		maxn = max(maxn, fa[i][i + n - 1]);
		minn = min(minn, fi[i][i + n - 1]);
	}
	cout << minn << endl << maxn << endl;
}
