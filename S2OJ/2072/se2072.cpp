#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 2, K = (1 << 8) + 10;
int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
vector<int>a[10][N];
int f[K][N][2];
struct Node
{
	int u, dis;
	Node(int _u, int _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const
	{
		return dis > rhs.dis;
	}
};
bool vis[N];
void dijkstra(int S, int ty)
{
	priority_queue<Node>q;
	for(int i = 1; i <= n; i++)
		vis[i] = false, q.emplace(i, f[S][i][ty]);
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u] = true;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[S][v][ty] > f[S][u][ty] + w[i])
			{
				f[S][v][ty] = f[S][u][ty] + w[i];
				q.emplace(v, f[S][v][ty]);
			}
		}
	}
}
int g[K][2];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	memset(f, 63, sizeof(f));
	int ecnt, maxt;
	scanf("%d%d", &ecnt, &maxt);
	for(int i = 1; i <= ecnt; i++)
	{
		int p, x, t;
		scanf("%d%d%d", &p, &x, &t);
		a[p][x].push_back(t);
	}
	for(int i = 1; i <= k; i++)
		for(int j = 1; j <= n; j++)
			sort(a[i][j].begin(), a[i][j].end()), \
			a[i][j].push_back(0x3f3f3f3f);
	int s0, s1;
	scanf("%d%d", &s0, &s1);
	f[0][s0][0] = 0, f[0][s1][1] = 0;
	for(int S = 0; S < (1 << k); S++)
	{
		dijkstra(S, 0), dijkstra(S, 1);
		for(int ty = 0; ty < 2; ty++)
		{
			for(int x = 1; x <= n; x++)
			{
				if(f[S][x][ty] > maxt)continue;
				int now = f[S][x][ty];
				for(int i = 1; i <= k; i++)
				{
					if(S & (1 << (i - 1)))continue;
					int v = lower_bound(a[i][x].begin(), a[i][x].end(), now) - a[i][x].begin();
					v = a[i][x][v];
					f[S | (1 << (i - 1))][x][ty] = min(f[S | (1 << (i - 1))][x][ty], v);
				}
			}
		}
	}
	memset(g, 63, sizeof(g));
	for(int S = 0; S < (1 << k); S++)
		for(int ty = 0; ty < 2; ty++)
			for(int i = 1; i <= n; i++)
				g[S][ty] = min(g[S][ty], f[S][i][ty]);
	int U = (1 << k) - 1;
	int ans = 0x3f3f3f3f;
	for(int S = 0; S < (1 << k); S++)
		for(int T = 0; T < (1 << k); T++)
			if((S | T) == U)
				ans = min(ans, max(g[S][0], g[T][1]));
	if(ans > maxt)puts("-1");
	else printf("%d\n", ans);
	return 0;
}
