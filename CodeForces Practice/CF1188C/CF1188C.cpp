#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = 100010;
const ll mod = 998244353;
int n, k;
int a[N];
ll f[N][N], sum[N][N];
ll res[M], ans;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	a[0] = -1e9;
	for(int v = 1; v * (k - 1) <= a[n]; v++)
	{
		f[0][0] = 1;
		int now = 0;
		sum[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			while(a[now] <= a[i] - v)now++;
			for(int j = 0; j <= k; j++)
			{
				if(j)f[i][j] = sum[now - 1][j - 1];
				sum[i][j] = (sum[i - 1][j] + f[i][j]) % mod;
			}
			res[v] += f[i][k];
		}
		ans = (ans + res[v]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
