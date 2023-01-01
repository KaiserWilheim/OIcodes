#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = N << 1;
const ll mod = 1000003;
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
int n, m;
char a[N][N];
int len, up;
int pos[N], cnt;
ll ans[N];
ll sum, tot;
ll C[N][N];
void dfs(int p, int now)
{
	if(p == n + 1)
	{
		if(now != up)return;
		ll tmp = 1;
		for(int j = 1; j <= len; j++)
		{
			int last = -1;
			for(int i = 1; i <= up; i++)
			{
				if(a[pos[i]][j] != '?')
				{
					if(last == -1)last = a[pos[i]][j] - 'a';
					else if(last != a[pos[i]][j] - 'a')return;
				}
			}
			if(last == -1)tmp = tmp * 26 % mod;
		}
		tot = (tot + tmp) % mod;
		return;
	}
	if(now < up)
	{
		pos[++cnt] = p;
		dfs(p + 1, now + 1);
		pos[cnt--] = 0;
	}
	if(n - p >= up - now)dfs(p + 1, now);
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", a[i] + 1);
	len = strlen(a[1] + 1);
	for(int i = n; i >= m; i--)
	{
		tot = 0, up = i;
		dfs(1, 0);
		sum = 0;
		for(int j = i + 1; j <= n; j++)
			sum = (sum + ans[j] * C[j][i] % mod) % mod;
		ans[i] = (tot - sum + mod) % mod;
	}
	printf("%lld\n", ans[m]);
}
int main()
{
	for(int i = 0; i <= 100; i++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(ans, 0, sizeof(ans));
		solve();
	}
	return 0;
}
