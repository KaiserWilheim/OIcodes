#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = 400010;
const int INF = 0x3f3f3f3f;
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
	for(int i = 1; i <= n; i++)dis[i] = -INF;
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
	int c;
	scanf("%d%d%d", &n, &m, &c);
	for(int i = 1; i <= n; i++)
	{
		int s;
		scanf("%d", &s);
		add(0, i, s);
	}
	for(int i = 1; i <= c; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	spfa(0);
	for(int i = 1; i <= n; i++)
		printf("%d\n", dis[i]);
	return 0;
}
