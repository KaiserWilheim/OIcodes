#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010, M = N << 1;
const ll mod = 1e8 + 7;
int n, m, q;
int c[N], v[N], t[N];
vector<pair<int, int>>p[N];
ll f[N][N], g[N][N], h[N];
void solve()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &t[i]);
	for(int i = 1; i <= n; i++)
		p[i].clear();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= t[i]; j++)
			p[i].emplace_back(j * c[i], j * v[i]), t[i] -= j;
		if(t[i])p[i].emplace_back(t[i] * c[i], t[i] * v[i]);
	}
	memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
	f[0][0] = g[n + 1][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = m; j >= 0; j--)
			f[i][j] = max(f[i][j], f[i - 1][j]);
		for(auto k : p[i])
			for(int j = m; j >= k.first; j--)
				f[i][j] = max(f[i][j], f[i][j - k.first] + k.second);
	}
	for(int i = n; i >= 1; i--)
	{
		for(int j = m; j >= 0; j--)
			g[i][j] = max(g[i][j], g[i + 1][j]);
		for(auto k : p[i])
			for(int j = m; j >= k.first; j--)
				g[i][j] = max(g[i][j], g[i][j - k.first] + k.second);
	}
	ll lans = 0;
	while(q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		int l = min((x + lans - 1) % n + 1, (y + lans - 1) % n + 1);
		int r = max((x + lans - 1) % n + 1, (y + lans - 1) % n + 1);
		memset(h, -1, sizeof(h));
		for(int i = 0; i <= m; i++)
			for(int j = 0; j + i <= m; j++)
				h[i + j] = max(h[i + j], f[l - 1][i] + g[r + 1][j]);
		lans = 0;
		for(int i = 1; i <= m; i++)
			lans += h[i];
		lans %= mod;
		ll sum = 0;
		for(int i = 1; i <= m; i++)sum ^= h[i];
		printf("%lld %lld\n", lans, sum);
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
