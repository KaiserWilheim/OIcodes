#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m, k;
vector<int>e[N];
int deg[N];
int vis[N];
void solve()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
	{
		e[i].clear();
		deg[i] = 0;
		vis[i] = 0;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
		deg[v]++, deg[u]++;
	}
	for(int i = 1; i <= n; i++)
		sort(e[i].begin(), e[i].end());
	queue<int>q;
	for(int i = 1; i <= n; i++)
		if(deg[i] < k)vis[i] = 1, q.push(i);
	vector<int>cli;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 2;
		if(deg[u] == k - 1 && cli.empty() && 1ll * k * (k - 1) / 2 <= m)
		{
			cli.push_back(u);
			for(auto v : e[u])
				if(vis[v] <= 1)cli.push_back(v);
			bool flag = true;
			for(auto x : cli)
			{
				for(auto y : cli)
				{
					if(x == y)break;
					if(!binary_search(e[x].begin(), e[x].end(), y))flag = false;
				}
			}
			if(!flag)cli.clear();
		}
		for(auto v : e[u])
			if(--deg[v] < k && !vis[v])
				vis[v] = 1, q.push(v);
	}
	if(count(vis + 1, vis + 1 + n, 0) > 0)
	{
		vector<int>ans;
		for(int i = 1; i <= n; i++)
			if(!vis[i])ans.push_back(i);
		printf("1 %d\n", ans.size());
		for(auto i : ans)
			printf("%d ", i);
		putchar('\n');
	}
	else if(!cli.empty())
	{
		puts("2");
		for(int i = 0; i < k; i++)
			printf("%d ", cli[i]);
		putchar('\n');
	}
	else puts("-1");
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
