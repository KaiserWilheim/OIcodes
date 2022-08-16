#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 10;
int mu[N], prime[N], vis[N];
vector<int> d[N];
int n, m, mod;
int l, h;
void moebius(int n)
{
	mu[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(!vis[i]) prime[++prime[0]] = i, mu[i] = mod - 1;
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = mod - mu[i];
		}
	}
}
int sum(int n)
{
	return ((1ll * (1 + n) * n) >> 1) % mod;
}
int solve()
{
	int ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		int lim = min(m, (int)sqrt(1ll * h * h - 1ll * i * i));
		int lim2 = max(1, (int)ceil(sqrt(1ll * l * l - 1ll * i * i)));
		for(auto p : d[i])
		{
			if(lim / p >= (lim2 - 1) / p + 1)
				ans = (ans + 1ll * (n - i + 1) * (m + 1) % mod * mu[p] % mod * ((lim / p) - ((lim2 - 1) / p + 1) + 1) % mod) % mod;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		int lim = min(m, (int)sqrt(1ll * h * h - 1ll * i * i));
		int lim2 = max(1, (int)ceil(sqrt(1ll * l * l - 1ll * i * i)));
		for(auto p : d[i])
		{
			if(lim / p >= (lim2 - 1) / p + 1)
				ans = (ans + mod - 1ll * (n - i + 1) * p % mod * mu[p] % mod * (sum(lim / p) + mod - sum(((lim2 - 1) / p + 1) - 1)) % mod) % mod;
		}
	}
	return (ans + ans) % mod;
}

int main()
{
	scanf("%d%d", &n, &m);
	scanf("%d%d", &l, &h);
	scanf("%d", &mod);
	moebius(n);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; j += i)
			d[j].push_back(i);

	int ans = solve();
	if(l == 1)
		ans = (ans + (1ll * n * (m + 1) % mod + 1ll * (n + 1) * m % mod) % mod) % mod;

	printf("%d\n", ans);
	return 0;
}
