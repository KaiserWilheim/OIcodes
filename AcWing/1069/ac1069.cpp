#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n;
ll w[N];
__int128 a[N];
__int128 f[N][N];
void write(__int128 x)
{
	int t[110];
	int tot = 0;
	while(x > 0)
	{
		t[++tot] = x % 10;
		x /= 10;
	}
	for(int i = tot; i >= 1; i--)
		printf("%d", t[i]);
	return;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &w[i]);
		a[i] = w[i];
	}
	for(int len = 3; len <= n; len++)
	{
		for(int l = 1; l + len - 1 <= n; l++)
		{
			int r = l + len - 1;
			f[l][r] = 1e40;
			for(int k = l + 1; k < r; k++)
			{
				f[l][r] = min(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
			}
		}
	}
	write(f[1][n]);
	putchar('\n');
	return 0;
}
