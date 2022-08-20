#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 250010;
int l[N], r[N], sum[N];
const int mod = 1e9 + 7;
int a[N], f[N];
int tong[N];
int main()
{
	int n;
	scanf("%dd", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tong[a[i]] = i;
	}
	int ans = 0;
	for(int i = n; i >= 1; i--)
	{
		f[i] = 1;
		for(int j = a[i] & (a[i] - 1); j; j = a[i] & (j - 1))
			if(tong[j] > i)f[i] = (f[i] + f[tong[j]]) % mod;
		ans = (ans + f[i]) % mod;
	}
	ans = (ans - n + mod) % mod;
	printf("%d\n", ans);
	return 0;
}