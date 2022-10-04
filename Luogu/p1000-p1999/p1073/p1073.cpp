#include <bits/stdc++.h>
using namespace std;
const int N = 300010, M = 5000010;
int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
int dis[N], vis[N];
void spfa(int s)
{
	queue<int>q;
	memset(dis, 0xc1, sizeof(dis));
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
			if(dis[v] < dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				if(!vis[v])
				{
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}
int val[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &val[i]);
		add(i, i + n, -val[i]);
		add(i + n, i + 2 * n, val[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v, type;
		scanf("%d%d%d", &u, &v, &type);
		add(u, v, 0);
		add(u + n, v + n, 0);
		add(u + 2 * n, v + 2 * n, 0);
		if(type == 2)
		{
			add(v, u, 0);
			add(v + n, u + n, 0);
			add(v + 2 * n, u + 2 * n, 0);
		}
	}
	spfa(1);
	printf("%d\n", dis[3 * n]);
	return 0;
}