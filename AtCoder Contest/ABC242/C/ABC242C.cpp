#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
long long p = 998244353;
long long f[N][10];
int n;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= 9; i++)f[1][i] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i][1] = (f[i - 1][1] + f[i - 1][2]) % p;
		for(int j = 2; j < 9; j++)
		{
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] + f[i - 1][j + 1]) % p;
		}
		f[i][9] = (f[i - 1][8] + f[i - 1][9]) % p;
	}
	long long ans = 0;
	for(int i = 1; i <= 9; i++)ans += f[n][i];
	printf("%lld\n", ans % p);
	return 0;
}
