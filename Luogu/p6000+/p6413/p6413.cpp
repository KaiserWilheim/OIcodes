#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010, M = 10010;
const ll mod = 1e9 + 7;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
ll ans[M];
struct Node
{
	int u, dis;
	Node(int _u, int _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const { return dis > rhs.dis; }
};
int dis[N], vis[N];
void dijkstra(int s)
{
	priority_queue<Node>q;
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	q.emplace(s, 0), dis[s] = 0;
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				q.emplace(v, dis[v]);
			}
		}
	}
}
ll num[2][N];
int sta[N], tt, deg[N];
bool tag[M];
void topo(int s)
{
	memset(num, 0, sizeof(num));
	memset(deg, 0, sizeof(deg));
	memset(tag, 0, sizeof(tag));
	tt = 0;
	dijkstra(s);
	for(int i = 1; i <= n; i++)
		for(int j = h[i]; ~j; j = ne[j])
			if(dis[e[j]] == dis[i] + w[j])
				tag[j] = true, deg[e[j]]++;
	queue<int>q;
	q.push(s), num[0][s] = 1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		sta[++tt] = u;
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(!tag[i])continue;
			int v = e[i];
			num[0][v] = add(num[0][v], num[0][u]);
			if(!--deg[v])q.push(v);
		}
	}
	while(tt)
	{
		int u = sta[tt--];
		num[1][u]++;
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(!tag[i])continue;
			num[1][u] = add(num[1][u], num[1][e[i]]);
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = h[i]; ~j; j = ne[j])
			if(tag[j])ans[j] = add(ans[j], num[0][i] * num[1][e[j]] % mod);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	for(int i = 1; i <= n; i++)topo(i);
	for(int i = 0; i < m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
