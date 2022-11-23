#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 410;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x = mod - 2)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
int n;
ll a[N][N * 2];
void GaussJordan()
{
	for(int i = 1; i <= n; i++)
	{
		int r = i;
		for(int j = i + 1; j <= n; j++)
			if(a[j][i] > a[r][i])r = j;
		if(r != i)swap(a[i], a[r]);
		if(!a[i][i])
		{
			puts("No Solution");
			exit(0);
		}
		ll b = qpow(a[i][i]);
		for(int k = 1; k <= n; k++)
		{
			if(k == i)continue;
			ll p = a[k][i] * b % mod;
			for(int j = i; j <= n * 2; j++)
				a[k][j] = ((a[k][j] - p * a[i][j]) % mod + mod) % mod;
		}
		for(int j = 1; j <= n * 2; j++)
			a[i][j] = a[i][j] * b % mod;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%lld", &a[i][j]);
	for(int i = 1; i <= n; i++)
		a[i][i + n] = 1;
	GaussJordan();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			printf("%lld ", a[i][j + n]);
		putchar('\n');
	}
	return 0;
}
