#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310, M = 100010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
struct Node
{
	int u, dis;
	Node(int _u, int _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const { return dis > rhs.dis; }
};
int fa[N], dis[N];
void dijkstra(int s)
{
	priority_queue<Node>q;
	memset(dis, 63, sizeof(dis));
	dis[s] = 0;
	q.emplace(s, 0);
	while(!q.empty())
	{
		int u = q.top().u;
		int d = q.top().dis;
		q.pop();
		if(dis[u] != d)continue;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				fa[v] = u;
				q.emplace(v, dis[v]);
			}
		}
	}
}
vector<int>g[N];
double f[N][N], a[N][N];
void dfs(int p, int fa)
{
	if(g[p].empty())
	{
		for(int i = 1; i <= k; i++)f[p][i] = a[p][i];
		return;
	}
	for(auto v : g[p])
	{
		dfs(v, p);
		for(int j = k; j >= 1; j--)
			for(int i = 1; i <= j; i++)
				f[p][j] = max(f[p][j], f[p][j - i] + f[v][i]);
	}
	int cnt = g[p].size();
	for(int i = 1; i <= k; i++)
		f[p][i] = f[p][i] / cnt;
	for(int j = k; j >= 1; j--)
		for(int i = 1; i <= j; i++)
			f[p][j] = max(f[p][j], a[p][i] + f[p][j - i] * (1 - a[p][i]));
}
int main()
{
	memset(h, -1, sizeof(h));
	n = read(), m = read(), k = read();
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		u = read(), v = read(), w = read();
		add(u, v, w), add(v, u, w);
	}
	dijkstra(1);
	for(int i = 2; i <= n; i++)g[fa[i]].push_back(i);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			scanf("%lf", &a[i][j]);
	dfs(1, 0);
	double res = 0;
	for(int i = 1; i <= k; i++)res = max(res, f[1][i]);
	printf("%.6lf\n", res);
	return 0;
}
