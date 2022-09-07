#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310, M = 100010;
const ll mod = 1e9 + 7;
int n, m;
int a[N], b[N];
int fa[N];
ll dp[N][M];
ll ans;
int h[N], e[N], ne[N], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u)
{
	for(int i = 1; i <= m + 1; i++)
		dp[u][i] = 1;
	for(int i = h[u]; ~i; i = ne[i])
	{
		int v = e[i];
		dfs(v);
		for(int j = 1; j <= m + (u == 0); j++)
		{
			if(j - a[v] < 0)continue;
			dp[u][j] = (dp[u][j] * dp[v][j - a[v]]) % mod;
		}
	}
	if(u != 0)
		for(int i = 1; i <= m + 1; i++)
			dp[u][i] = (dp[u][i] + dp[u][i - 1]) % mod;
}
int main()
{
	memset(h, -1, sizeof(h));
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	for(int i = 1; i <= n; i++)
	{
		a[i] = 1;
		if(b[i] == -1)
		{
			fa[i] = 0;
			continue;
		}
		for(int j = b[i] + 1; j < i; j++)
		{
			if(fa[j] <= b[i])
			{
				fa[j] = i;
				a[j] = 0;
			}
		}
		fa[i] = b[i];
	}
	for(int i = 1; i <= n; i++)
		add(fa[i], i);
	dfs(0);
	cout << dp[0][m + 1] << endl;
	return 0;
}