#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 4;
int n, m;
ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}
ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
vector<int>f[N];
int w[N], deg[N];
bool vis[N], s[N];
int dp[N], to[N];
void dfs(int p)
{
	if(dp[p])return;
	dp[p] = w[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		dfs(e[i]);
		if(dp[p] < dp[e[i]] + w[p])
			dp[p] = dp[e[i]] + w[p], to[p] = e[i];
	}
}
int sta[N], tt;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		vis[x] = true;
	}
	for(int i = 1; i <= m; i++)
	{
		if(vis[i])continue;
		int k = gcd(i, m);
		f[k].push_back(i), w[k]++;
		if(s[k])continue;
		s[k] = true;
		for(int j = 2 * k; j < m; j += k)
			add(k, j), deg[j]++;
	}
	queue<int>q;
	for(int i = 1; i < m; i++)
		if(s[i] && !deg[i])q.push(i);
	int ans = 0, ansp = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		dfs(u);
		if(ans < u)ans = dp[u], ansp = u;
	}
	for(int i = ansp; i; i = to[i])
		for(auto k : f[i])
			sta[++tt] = k;
	if(!vis[0])sta[++tt] = 0;
	printf("%d\n", tt);
	if(tt == 0)return 0;
	printf("%d ", sta[1]);
	for(int i = 2; i <= tt; i++)
	{
		if(sta[i] == 0)printf("%d ", sta[i]);
		else
		{
			ll x, y;
			ll k = exgcd(sta[i - 1], m, x, y);
			ll dx = m / k, tp = sta[i] / k;
			while(x < 0)x += dx;
			x %= dx;
			x = x * tp;
			printf("%d ", x % m);
		}
	}
	putchar('\n');
	return 0;
}
