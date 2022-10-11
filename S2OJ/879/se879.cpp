#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 23333333;
int n, m;
ll f[N], sum[N];
ll g[N], s[N], h[N];
int main()
{
	scanf("%d", &n);
	int S = ceil(sqrt(n));
	f[0] = 1;
	for(int i = 1; i < S; i++)
	{
		memset(sum, 0, sizeof(sum));
		for(int j = 0; j <= n; j++)
			sum[j] = ((j >= i ? sum[j - i] : 0) + f[j]) % mod;
		memset(f, 0, sizeof(f));
		for(int j = 0; j <= n; j++)
			f[j] = (sum[j] - (j >= (i + 1) * i ? sum[j - (i + 1) * i] : 0) + mod) % mod;
	}
	g[0] = 1, s[0] = 1;
	for(int i = 1; i <= S; i++)
	{
		memcpy(h, g, sizeof(h));
		memset(g, 0, sizeof(g));
		for(int j = i * S; j <= n; j++)
		{
			g[j] = (g[j - i] + h[j - S]) % mod;
			s[j] = (s[j] + g[j]) % mod;
		}
	}
	ll res = 0;
	for(int i = 0; i <= n; i++)
		res = (res + s[i] * f[n - i]) % mod;
	printf("%lld\n", res);
	return 0;
}