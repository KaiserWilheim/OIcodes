#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll mod = 998244353;
int n;
int s[N];
ll f[N], sum[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			s[j]++;
	f[1] = 1, sum[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i] = (s[i] + sum[i - 1]) % mod;
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
	printf("%lld\n", f[n]);
	return 0;
}