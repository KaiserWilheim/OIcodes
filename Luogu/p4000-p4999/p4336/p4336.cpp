#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20, M = N * N;
const ll mod = 1e9 + 7;
int n, maxn;
int m[N];
int u[N][M], v[N][M];
int sz[(1 << 18)];
ll krh[N][N];
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
inline ll det()
{
	ll res = 1;
	int flag = 0;
	for(int i = 1; i <= n - 1; i++)
	{
		if(krh[i][i] == 0)
		{
			for(int j = i + 1; j <= n - 1; j++)
			{
				if(krh[j][i] == 0)continue;
				flag ^= 1;
				for(int k = 1; k <= n - 1; k++)
					swap(krh[i][k], krh[j][k]);
			}
		}
		for(int j = i; j <= n - 1; j++)
		{
			if(krh[j][i] == 0)continue;
			ll inv = qpow(krh[j][i], mod - 2);
			res = (res * krh[j][i]) % mod;
			for(int k = i; k <= n - 1; k++)
				krh[j][k] = (krh[j][k] * inv) % mod;
		}
		for(int j = i + 1; j <= n - 1; j++)
		{
			if(krh[j][i] == 0)continue;
			for(int k = i; k <= n - 1; k++)
				krh[j][k] = (krh[j][k] - krh[i][k] + mod) % mod;
		}
	}
	for(int i = 1; i <= n - 1; i++)
		res = (res * krh[i][i]);
	return (flag) ? (mod - res) % mod : res;
}
int main()
{
	scanf("%d", &n);
	maxn = (1 << (n - 1)) - 1;
	for(int i = 1; i < n; i++)
	{
		scanf("%d", &m[i]);
		for(int j = 1; j <= m[i]; j++)
			scanf("%d%d", &u[i][j], &v[i][j]);
	}
	for(int i = 1; i <= maxn; i++)
		sz[i] = sz[i >> 1] + (i & 1);
	ll res = 0;
	for(int i = 1; i <= maxn; i++)
	{
		memset(krh, 0, sizeof(krh));
		for(int j = 1, p = i; p; p >>= 1, j++)
		{
			if((p & 1) == 0)continue;
			for(int k = 1; k <= m[j]; k++)
			{
				int U = u[j][k], V = v[j][k];
				krh[U][U]++, krh[V][V]++;
				krh[U][V] = (krh[U][V] + mod - 1) % mod;
				krh[V][U] = (krh[V][U] + mod - 1) % mod;
			}
		}
		res = (res + mod + det() * ((n - sz[i]) % 2 ? 1 : -1)) % mod;
	}
	printf("%lld\n", res);
	return 0;
}
