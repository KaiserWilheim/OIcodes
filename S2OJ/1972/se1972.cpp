#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310, M = 90010;
int n;
ll mod;
ll f[N][N], d[N];
ll pow2[M];
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int main()
{
	scanf("%d%lld", &n, &mod);
	pow2[0] = 1;
	for(int i = 1; i <= n * n; i++)
		pow2[i] = pow2[i - 1] * 2 % mod;
	f[1][1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i][1] = pow2[(i - 1) * (i - 2) / 2];
		for(int j = 2; j <= i; j++)
			for(int k = 1; k < i; k++)
				f[i][j] = add(f[i][j], f[k][j - 1] * pow2[(i - k - 2) * (i - k - 1) / 2] % mod);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
			d[i] = add(d[i], f[i][j] * d[j] % mod);
		d[i] = add(pow2[i * (i + 1) / 2], mod - d[i]);
	}
	printf("%lld\n", d[n]);
	return 0;
}
