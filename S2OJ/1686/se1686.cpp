#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 5010;
const ll mod = 998244353;
int n, m;
int a[N];
ll f[M][M];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int b = 1 << 8;
	for(int i = 0; i < b; i++)
		f[0][i] = 1;
	for(int i = 1; i <= n; i++)
	{
		int p = a[i] % b, q = a[i] / b;
		ll ans = 0;
		for(int j = p; ; j = (j - 1) & p)
		{
			ans = (ans + f[j][q]) % mod;
			if(!j)break;
		}
		q ^= 255;
		for(int j = q; ; j = (j - 1) & q)
		{
			f[p][j ^ 255] = (f[p][j ^ 255] + ans) % mod;
			if(!j)break;
		}
		printf("%lld\n", ans);
	}
	return 0;
}