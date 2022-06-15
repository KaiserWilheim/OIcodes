#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = 200010;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dis[N], vis[N];
void spfa(int s)
{
	queue<int>q;
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
					vis[v] = 1;
					q.push(v);
				}
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
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		add(u, v, k);
		add(v + n, u + n, k);
	}
	spfa(1);
	int ans = 0;
	for(int i = 2; i <= n; i++)
		ans += dis[i];
	spfa(n + 1);
	for(int i = n + 2; i <= n + n; i++)
		ans += dis[i];
	printf("%d\n", ans);
	return 0;
}
