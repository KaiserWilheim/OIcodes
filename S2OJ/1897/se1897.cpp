#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') { f = -1; }c = getchar(); }
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x * f;
}
const int N = 20, M = 40;
int n, m;
int h[N], e[M], ne[M], idx;
bool g[N][N];
bool vis[N];
int tmp[N], tt;
ll f[N][N];
ll ans;
void add(int a, int b)
{
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
	e[++idx] = a, ne[idx] = h[b], h[b] = idx;
}
void dfs(int p, int fa)
{
	int i, j, k;
	for(i = h[p]; i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
	}
	for(int i = 1; i <= tt; i++)
	{
		int x = tmp[i];
		f[p][x] = 1;
		for(j = h[p]; j; j = ne[j])
		{
			if(e[j] == fa)continue;
			ll sum = 0;
			for(k = 1; k <= tt; k++)
			{
				int y = tmp[k];
				if(!g[x][y])continue;
				sum += f[e[j]][y];
			}
			f[p][x] *= sum;
		}
	}
}
void solve()
{
	int i;
	tt = 0;
	for(i = 1; i <= n; i++)
		if(vis[i])tmp[++tt] = i;
	dfs(1, 0);
	for(i = 1; i <= tt; i++)
		if((n - tt) & 1)ans -= f[1][tmp[i]];
		else ans += f[1][tmp[i]];
}
void DFS(int dep)
{
	if(dep == n + 1)return solve();
	vis[dep] = false;
	DFS(dep + 1);
	vis[dep] = true;
	DFS(dep + 1);
}
int main()
{
	int i, x, y;
	n = read(), m = read();
	for(i = 1; i <= m; i++)
	{
		x = read(), y = read();
		g[x][y] = g[y][x] = true;
	}
	for(i = 1; i < n; i++)
	{
		x = read(), y = read();
		add(x, y);
	}
	DFS(1);
	printf("%lld\n", ans);
	return 0;
}
