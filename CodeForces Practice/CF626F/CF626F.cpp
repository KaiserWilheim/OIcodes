#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
const ll mod = 1e9 + 7;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n, m;
int a[N], b[N];
ll f[2][N][N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i < n; i++)
		b[i] = a[i + 1] - a[i];
	f[0][0][0] = f[0][1][0] = 1;
	for(int i = 1; i < n; i++)
	{
		int now = i & 1;
		for(int j = 0; j <= n; j++)
		{
			int tmp = b[i] * j;
			for(int k = 0; k <= m; k++)
			{
				int val = k + tmp;
				ll res = f[now ^ 1][j][k], v = res * j % mod;
				f[now ^ 1][j][k] = 0;
				if(val > m)continue;
				if(j)f[now][j - 1][val] = add(f[now][j - 1][val], v);
				f[now][j][val] = add(f[now][j][val], add(v, res));
				f[now][j + 1][val] = add(f[now][j + 1][val], res);
			}
		}
	}
	ll ans = 0;
	for(int i = 0; i <= m; i++)
		ans = add(ans, f[(n & 1) ^ 1][0][i]);
	printf("%lld\n", ans);
	return 0;
}
