#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20010, M = 100010;
int n, m;
int hp;
int f[N];
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dis[N], vis[N];
void spfa(int k)
{
	queue<int>q;
	memset(dis, 63, sizeof(dis));
	dis[1] = 0, vis[1] = 1;
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i] && f[v] <= k)
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
	scanf("%d", &hp);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &f[i]);
		maxn = max(maxn, f[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		add(u, v, k);
		add(v, u, k);
	}
	spfa(maxn + 1);
	if(dis[n] > hp)
	{
		puts("AFK");
		return 0;
	}
	int l = 0, r = maxn;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		spfa(mid);
		if(dis[n] > hp)l = mid + 1;
		else r = mid;
	}
	printf("%d\n", max(r, f[1]));
	return 0;
}
