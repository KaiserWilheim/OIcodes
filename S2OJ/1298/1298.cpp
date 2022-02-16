#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200020, M = 110, mod = 1e9 + 7;
ll T, n, m, k;
ll a[N], fac[N], inv[N];
ll t[M], f[M][M], pre[M];
ll qpow(ll x, ll k)
{
	ll ans = 1;
	while(k)
	{
		if(k & 1)ans = (ans * x) % mod;
		x = (x * x) % mod;
		k >>= 1;
	}
	return ans;
}
ll C(ll b, ll a)
{
	return (((fac[b] * inv[a]) % mod) * (inv[b - a])) % mod;
}
void init()
{
	fac[0] = 1ll;
	for(int i = 1; i < N; i++)fac[i] = (fac[i - 1] * i) % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; i--)inv[i] = ((i + 1) * inv[i + 1]) % mod;
}
int main()
{
	init();
	scanf("%lld%lld", &n, &T);
	for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	while(T--)
	{
		memset(t, 0, sizeof(t));
		memset(f, 0, sizeof(f));
		scanf("%lld", &m);
		for(int i = 1; i <= n; i++)t[(a[i] % m + m) % m]++;
		f[0][0] = qpow(2, t[0]);
		for(int i = 1; i < m; i++)
		{
			memset(pre, 0, sizeof(pre));
			for(int k = 0; k <= t[i]; k++)pre[k % m] = (pre[k % m] + C(t[i], k)) % mod;
			for(int j = 0; j < m; j++)
			{
				for(int k = 0; k <= min(m - 1, t[i]); k++)
				{
					f[i][(j + i * k) % m] = (f[i][(j + i * k) % m] + f[i - 1][j] * pre[k] % mod) % mod;
				}
			}
		}
		printf("%lld\n", f[m - 1][0]);
	}
	return 0;
}
