#include<bits/stdc++.h>
using namespace std;
const int N = 3000050;
const int INF = 0x3f3f3f3f;
int n, k;
int h[N], e[N], ne[N], w[N], idx;
int dis[N], tot[N];
bool vis[N];
void add(int a, int b, int c)
{
	e[++idx] = b;
	ne[idx] = h[a];
	h[a] = idx;
	w[idx] = c;
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
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++)
	{
		int op, u, v;
		scanf("%d%d%d", &op, &u, &v);
		if(op == 1)
		{
			add(u, v, 0);
			add(v, u, 0);
		}
		else if(op == 2)
		{
			if(u == v)
			{
				puts("-1");
				return 0;
			}
			add(u, v, 1);
		}
		else if(op == 3)
		{
			add(v, u, 0);
		}
		else if(op == 4)
		{
			if(v == u)
			{
				puts("-1");
				return 0;
			}add(v, u, 1);
		}
		else if(op == 5)
		{
			add(u, v, 0);
		}
	}
	for(int i = n; i >= 1; i--)
		add(0, i, 1);
	if(!spfa(0))
	{
		puts("-1");
	}
	else
	{
		long long ans = 0;
		for(int i = 1; i <= n; i++)
			ans += dis[i];
		printf("%lld\n", ans);
	}
	return 0;
}
