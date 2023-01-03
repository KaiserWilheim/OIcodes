#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 1000010;
int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int deg[N];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void adds(int a, int b)
{
	e[idx] = b, ne[idx] = hs[a], hs[a] = idx++, deg[b]++;
}
struct Node
{
	int u;
	ll dis;
	Node(){}
	Node(int _u, ll _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const
	{
		return dis > rhs.dis;
	}
};
ll dis[N];
void dijkstra(int s)
{
	memset(dis, 63, sizeof(dis));
	priority_queue<Node>q;
	q.emplace(s, 0);
	dis[s] = 0;
	while(!q.empty())
	{
		int u = q.top().u;
		ll d = q.top().dis;
		q.pop();
		if(dis[u] != d)continue;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > d + w[i])
			{
				dis[v] = d + w[i];
				q.emplace(v, dis[v]);
			}
		}
	}
}
int id[N], sz[N], tmp[N];
int main()
{
	memset(h, -1, sizeof(h));
	memset(hs, -1, sizeof(hs));
	int s;
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dijkstra(s);
	for(int u = 1; u <= n; u++)
	{
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] == dis[u] + w[i])adds(u, v);
		}
	}
	queue<int>q;
	q.push(s);
	for(int i = 1; i <= n; i++)tmp[i] = i;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if(tmp[u] != -1 && tmp[u] != s)id[u] = tmp[u];
		else id[u] = u;
		sz[id[u]]++;
		for(int i = hs[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(tmp[v] == v)tmp[v] = id[u];
			else if(tmp[v] != id[u])tmp[v] = -1;
			if(!--deg[v])q.push(v);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		if(i != s)ans = max(ans, sz[i]);
	printf("%d\n", ans);
	return 0;
}
