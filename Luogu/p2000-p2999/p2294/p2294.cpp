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
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(h, -1, sizeof(h));
		memset(vis, 0, sizeof(vis));
		memset(tot, 0, sizeof(tot));
		idx = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++)
		{
			int v, u, w;
			scanf("%d%d%d", &v, &u, &w);
			add(u, v - 1, w);
			add(v - 1, u, -w);
		}
		bool flag = false;
		for(int i = 0; i <= n; i++)
			if(!tot[i])
				if(!spfa(i))
				{
					flag = true;
					break;
				}
		if(flag)puts("false");
		else puts("true");
	}
	return 0;
}
