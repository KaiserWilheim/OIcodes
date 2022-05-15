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
void dfs(int p)
{
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!vis[j])
		{
			printf("%d %d\n", p, j);
			dfs(j);
		}
	}
}
void bfs(int p)
{
	queue<int>q;
	vis[p] = true;
	q.push(p);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if(!vis[j])
			{
				printf("%d %d\n", u, j);
				vis[j] = true;
				q.push(j);
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	memset(vis, 0, sizeof(vis));
	dfs(1);
	memset(vis, 0, sizeof(vis));
	bfs(1);
	return 0;
}
