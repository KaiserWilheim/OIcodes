#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4000010;
ll mod;
int n;
ll f[N], sum[N];
int main()
{
	scanf("%d%lld", &n, &mod);
	f[n] = 1;
	sum[n] = 1;
	for(int i = n - 1; i >= 1; i--)
	{
		f[i] = sum[i + 1];
		for(int j = 2; j * i <= n; j++)
			f[i] = (f[i] + (sum[j * i] - sum[min(j * i + j, n + 1)]) % mod + mod) % mod;
		sum[i] = (sum[i + 1] + f[i]) % mod;
	}
	printf("%lld\n", f[1]);
	return 0;
}
