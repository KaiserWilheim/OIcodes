#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010;
int a[N], b[N];
int n;
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
		int val = 0;
		if(b[0] < a[i])val = f[i - 1][0];
		for(int j = 1; j <= n; j++)
		{
			if(a[i] == b[j])f[i][j] = val + 1;
			else f[i][j] = f[i - 1][j];
			if(b[j] < a[i])val = max(val, f[i - 1][j]);
		}
	}
	int maxn = 0;
	for(int i = 1; i <= n; i++)
		maxn = max(maxn, f[n][i]);
	cout << maxn << endl;
	return 0;
}
