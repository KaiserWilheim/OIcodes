#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
int n;
ll mod;
ll C[2][N];
ll f[N];
int main()
{
	scanf("%d%lld", &n, &mod);
	C[0][0] = C[1][0] = 1;
	f[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			if(j & 1)f[i] = (f[i] + f[j - 1] * f[i - j] % mod * C[(i - 1) & 1][j - 1] % mod) % mod;
			C[i & 1][j] = (C[(i - 1) & 1][j] + C[(i - 1) & 1][j - 1]) % mod;
		}
	}
	printf("%lld\n", f[n] * 2 % mod);
	return 0;
}
