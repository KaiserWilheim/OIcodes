#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010, M = 500010;
int m, n;
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
priority_queue<node, vector<node>, greater<node> >q;
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
int main()
{
	memset(h, -1, sizeof(h));
	int s;
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(u != v)add(u, v, w);
	}
	dijkstra(s);
	for(int i = 1; i <= n; i++)
		printf("%d ", (dis[i] == 0x3f3f3f3f) ? 0x7fffffff : dis[i]);
	putchar('\n');
	return 0;
}
