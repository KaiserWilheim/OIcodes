#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool vis[N];
vector<int>a, b;
void chq()
{
	bool used[N];
	memset(used, 0, sizeof(used));
	printf("%d %d\n", b.size(), a.size());
	for(int i : b)
	{
		printf("%d ", i);
		used[i] = true;
	}
	putchar('\n');
	for(int i : a)
	{
		printf("%d ", i);
		used[i] = true;
	}
	putchar('\n');
	for(int i = 1; i <= n; i++)
	{
		if(!used[i])printf("%d ", i);
	}
	putchar('\n');
	exit(0);
}
void dfs(int p, int fa)
{
	b.push_back(p);
	vis[p] = true;
	if(a.size() == n - a.size() - b.size())
	{
		chq();
		return;
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		dfs(e[i], p);
		if(a.size() == n - a.size() - b.size())
		{
			chq();
			return;
		}
	}
	b.pop_back();
	a.push_back(p);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!vis[i])dfs(i, 0);
	puts("-1");
	return 0;
}