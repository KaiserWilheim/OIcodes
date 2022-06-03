#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = 500010;
int h[N], e[M], ne[M], w[M], idx;
int tot[N], dis[N], vis[N];
int n, m, q;
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
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 2; i <= n; i++)
	{
		add(i, i - 1, 0);
		add(0, i, 0);
	}
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
	for(int i = 1; i <= q; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(b, a, -c);
	}
	if(!spfa(0))
	{
		puts("-1");
		return 0;
	}
	spfa(1);
	if(dis[n] == 0x3f3f3f3f)puts("-2");
	else printf("%d\n", dis[n]);
	return 0;
}
