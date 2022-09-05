#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 510;
const ll mod = 998244353;
int n, m;
vector<pair<int, int> >p;
ll f[N][N * 50];
ll qpow(ll a, int x)
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
ll calc(int x)
{
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i = 1; i <= 2 * m; i++)
		for(int j = 0; j <= x * m; j++)
			for(int k = 0; k <= min(j, x); k++)
				f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;
	return f[2 * m][x * m];
}
int main()
{
	scanf("%d%d", &n, &m);
	int tmp = n;
	for(int i = 2; i * i <= tmp; i++)
	{
		if(n % i == 0)
		{
			p.emplace_back(i, 0);
			while(n % i == 0)
			{
				p.back().second++;
				n /= i;
			}
		}
	}
	if(n != 1)p.emplace_back(n, 1);
	n = tmp;

	ll ans = 1;
	for(auto i : p)
		ans = (ans * calc(i.second)) % mod;

	ll tot = 0;
	for(int i = 1; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			tot++;
			if(i * i != n)tot++;
		}
	}
	tot = qpow(tot, 2 * m);

	ll res = (ans + tot) * ((mod + 1) / 2) % mod;
	printf("%lld\n", res);
	return 0;
}