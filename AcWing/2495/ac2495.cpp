#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 4000010;
int n, m, k;
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll arr[N], acc[N];
vector<int>pro[N];
int ind[N];
struct Node
{
	int u;
	ll dis;
	bool operator > (const Node &a) const
	{
		return dis > a.dis;
	}
};
ll dis[N], vis[N];
priority_queue<Node, vector<Node>, greater<Node>>q;
void dijkstra(int s)
{
	memset(dis, 63, sizeof(dis));
	memset(arr, 63, sizeof(arr));
	dis[s] = arr[s] = acc[s] = 0;
	q.push({ s,0 });
	while(!q.empty())
	{
		int p = q.top().u;
		q.pop();
		if(vis[p])continue;
		vis[p] = 1;
		for(int i = h[p]; ~i; i = ne[i])
		{
			int v = e[i];
			if(arr[v] > dis[p] + w[i])
			{
				arr[v] = dis[p] + w[i];
				if(!ind[v])
				{
					dis[v] = max(acc[v], arr[v]);
					q.push({ v,dis[v] });
				}
			}
		}
		for(int v : pro[p])
		{
			acc[v] = max(acc[v], dis[p]);
			ind[v]--;
			if(!ind[v])
			{
				dis[v] = max(acc[v], arr[v]);
				q.push({ v,dis[v] });
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
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w);
	}
	for(int i = 1; i <= n; i++)
	{
		int k, x;
		scanf("%d", &k);
		while(k--)
		{
			scanf("%d", &x);
			ind[i]++;
			pro[x].push_back(i);
		}
	}
	dijkstra(1);
	printf("%lld\n", dis[n]);
	return 0;
}