#include<bits/stdc++.h>
using namespace std;
const int N = 5010, M = 10010;
int e[M], ne[M], w[M], h[N], idx;
int tot[N], dis[N], vis[N];
int n, m;
void add(int a, int b, int c)
{
	e[++idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}
bool spfa(int s)
{
	queue<int> q;
	memset(dis, 63, sizeof(dis));
	dis[s] = 0, vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				if(!vis[v])
				{
					vis[v] = 1, tot[v]++;
					if(tot[v] == n + 1)return false;
					q.push(v);
				}
			}
		}
	}
	return true;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		add(0, i, 0);
	for(int i = 1; i <= m; i++)
	{
		int v, u, w;
		scanf("%d%d%d", &v, &u, &w);
		add(u, v, w);
	}
	if(!spfa(0))
	{
		puts("NO SOLUTION");
	}
	else
	{
		int minp = 0;
		for(int i = 1; i <= n; i++)minp = min(minp, dis[i]);
		for(int i = 1; i <= n; i++)
			printf("%d\n", dis[i] - minp);
	}
	return 0;
}
