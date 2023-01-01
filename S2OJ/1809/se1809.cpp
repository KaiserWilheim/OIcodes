#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n;
vector<int>h[N];
int f[N], g[N], cnt[N];
vector<int>ans;
void dfs(int p, int fa)
{
	f[p] = 0;
	if(h[p].empty())
	{
		if(g[p] == 0)f[p] = 1;
		if(g[p] == 1)f[p] = -1;
		cnt[p] = f[p];
		return;
	}
	for(int v : h[p])
	{
		if(v == fa)continue;
		dfs(v, p);
		f[p] += f[v];
	}
	cnt[p] = f[p];
	if(f[p] < 0)f[p] = -1;
	if(f[p] > 0)f[p] = 1;
}
void dfs1(int p, int fa)
{
	if(h[p].empty())
	{
		if(g[p] == -1)ans.emplace_back(p);
	}
	for(int v : h[p])
	{
		if(v == fa)continue;
		if(f[v] == 0 || cnt[v] == -1)dfs1(v, p);
	}
}
void dfs2(int p, int fa)
{
	if(h[p].empty())
	{
		if(g[p] == -1)ans.emplace_back(p);
	}
	for(int v : h[p])
	{
		if(v == fa)continue;
		dfs2(v, p);
	}
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		h[i].clear();
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		if(x)h[x].emplace_back(i);
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &g[i]);
	dfs(1, 0);
	if(f[1] < 0)
	{
		puts("-1");
	}
	else if(f[1] > 0)
	{
		dfs2(1, 0);
		sort(ans.begin(), ans.end());
		printf("%d ", ans.size());
		for(auto i : ans)
			printf("%d ", i);
		putchar('\n');
	}
	else
	{
		dfs1(1, 0);
		sort(ans.begin(), ans.end());
		printf("%d ", ans.size());
		for(auto i : ans)
			printf("%d ", i);
		putchar('\n');
	}
	ans.clear();
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