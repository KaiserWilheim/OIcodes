#include <bits/stdc++.h>
using namespace std;
const int N = 400010, M = 5000010;
int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
struct node
{
	int dis, u;
	bool operator > (const node &a) const
	{
		return dis > a.dis;
	}
};
int dis[N], vis[N];
priority_queue<node, vector<node>, greater<node>>q;
void dijkstra(int s)
{
	memset(dis, 63, sizeof(dis));
	dis[s] = 0;
	q.push({ 0,s });
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i], c = w[i];
			if(dis[v] > dis[u] + c)
			{
				dis[v] = dis[u] + c;
				if(!vis[v])q.push({ dis[v],v });
			}
		}
	}
}
struct Edge
{
	int u, v, w;
};
Edge edge[M];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	scanf("%d", &k);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = { u,v,w };
		add(u, v, w), add(v, u, w);
	}
	for(int i = 1; i <= k; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int u = edge[j].u, v = edge[j].v, w = edge[j].w;
			add(u + i * n, v + i * n, w);
			add(v + i * n, u + i * n, w);
			add(u + i * n - n, v + i * n, 0);
			add(v + i * n - n, u + i * n, 0);
		}
		add(i * n, i * n + n, 0);
	}
	dijkstra(1);
	printf("%d\n", dis[n + k * n]);
	return 0;
}
