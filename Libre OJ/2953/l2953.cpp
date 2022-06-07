#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010, M = N << 1;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
int n, m;
namespace tree
{
	vector<int>e[N];
	int ans[N];
	int cnt = 0;
	void dfs(int p, int fa)
	{
		ans[++cnt] = p;
		for(auto i : e[p])
		{
			if(i == fa)continue;
			dfs(i, p);
		}
	}
	void main()
	{
		memset(ans, 0, sizeof(ans));
		for(int i = 1; i <= m; i++)
		{
			int u = read(), v = read();
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 1; i <= n; i++)
			sort(e[i].begin(), e[i].end());
		dfs(1, 0);
		for(int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		putchar('\n');
		return;
	}
}
namespace cycle
{
	struct Edge
	{
		int u, v;
	}cyc[N];
	vector<int>e[N];
	int tot = 0;
	bool vis[N], flag = false;
	bool incyc[N];
	void find(int p, int fa)
	{
		vis[p] = true;
		for(auto i : e[p])
		{
			if(i == fa)continue;
			if(vis[i])
			{
				flag = true;
				incyc[i] = true;
				incyc[p] = true;
				cyc[++tot] = { p,i };
				return;
			}
			find(i, p);
			if(flag && incyc[i])
			{
				if(incyc[p])flag = false;
				else incyc[p] = true;
				cyc[++tot] = { p,i };
				return;
			}
		}
	}
	int ans[N], res[N];
	int cnt = 0;
	int cv, cu;
	void dfs(int p, int fa)
	{
		if(vis[p])return;
		ans[++cnt] = p;
		vis[p] = true;
		for(auto i : e[p])
		{
			if(i == fa)continue;
			if((p == cu && i == cv) || (p == cv && i == cu))continue;
			dfs(i, p);
		}
	}
	bool chq()
	{
		for(int i = 1; i <= n; i++)
		{
			if(ans[i] > res[i])return false;
			else if(ans[i] < res[i])return true;
		}
		return true;
	}
	void main()
	{
		for(int i = 1; i <= m; i++)
		{
			int u = read(), v = read();
			e[u].push_back(v);
			e[v].push_back(u);
		}
		memset(vis, false, sizeof(vis));
		memset(incyc, false, sizeof(incyc));
		find(1, 0);
		for(int i = 1; i <= n; i++)
			sort(e[i].begin(), e[i].end());
		for(int i = 1; i <= tot; i++)
		{
			memset(vis, false, sizeof(vis));
			cnt = 0;
			cu = cyc[i].u, cv = cyc[i].v;
			dfs(1, 0);
			if(i == 1 || chq())
			{
				for(int i = 1; i <= n; i++)
					res[i] = ans[i];
			}
		}
		for(int i = 1; i <= n; i++)
			printf("%d ", res[i]);
		putchar('\n');
		return;
	}
}
int main()
{
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	n = read(), m = read();
	if(m == n - 1)
		tree::main();
	else
		cycle::main();
	return 0;
}
