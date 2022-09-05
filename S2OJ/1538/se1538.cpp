#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int sdep[N], mdep;
void dfs(int p, int fa, int dep)
{
	mdep = max(mdep, dep);
	sdep[dep]++;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p, dep + 1);
	}
}
ll f[N], dp[N];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	memset(h, -1, sizeof(h));
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if(x == 0)continue;
		add(x, i), add(i, x);
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		memset(f, 0, sizeof(f));
		memset(dp, 0, sizeof(dp));
		for(int j = h[i]; ~j; j = ne[j])
		{
			memset(sdep, 0, sizeof(sdep));
			mdep = 0;
			dfs(e[j], i, 1);
			for(int k = 1; k <= mdep; k++)
			{
				ans += dp[k] * sdep[k];
				dp[k] += f[k] * sdep[k];
				f[k] += sdep[k];
			}
		}
	}
	cout << ans << endl;
	return 0;
}