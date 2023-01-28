#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N = 1010, M = N * N;
int n, m;
int S, T;
struct Node
{
	int u, dis;
	Node(int _u, int _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const
	{
		return dis > rhs.dis;
	}
};
vector<pii>e[M];
void add(int a, int b, int c)
{
	e[a].emplace_back(b, c);
}
int dis[M], vis[M];
void dijkstra()
{
	priority_queue<Node>q;
	memset(dis, 63, sizeof(dis));
	dis[S] = 0;
	q.emplace(S, 0);
	while(!q.empty())
	{
		Node now = q.top();
		q.pop();
		if(vis[now.u])continue;
		int u = now.u;
		vis[u] = true;
		for(auto i : e[u])
		{
			int v = i.first, w = i.second;
			if(dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				q.emplace(v, dis[v]);
			}
		}
	}
}
char s[N][N];
int l[N][N], r[N][N], u[N][N], d[N][N];
#define id(i, j) (((i) - 1) * m + (j))
int dx[5] = { 0,1,0,-1 }, dy[5] = { 1,0,-1,0 };
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(s[i][j] == '#')continue;
			if(s[i][j] == 'C')S = id(i, j);
			if(s[i][j] == 'F')T = id(i, j);
			l[i][j] = l[i][j - 1] + 1;
			u[i][j] = u[i - 1][j] + 1;
		}
	}
	for(int i = n; i; i--)
	{
		for(int j = m; j; j--)
		{
			if(s[i][j] == '#')continue;
			r[i][j] = r[i][j + 1] + 1;
			d[i][j] = d[i + 1][j] + 1;
			for(int k = 0; k < 4; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				if(s[nx][ny] == '#')continue;
				add(id(i, j), id(nx, ny), 1);
			}
			int dis = min(min(l[i][j], r[i][j]), min(u[i][j], d[i][j]));
			if(l[i][j] > 1)add(id(i, j), id(i, j - l[i][j] + 1), dis);
			if(r[i][j] > 1)add(id(i, j), id(i, j + r[i][j] - 1), dis);
			if(u[i][j] > 1)add(id(i, j), id(i - u[i][j] + 1, j), dis);
			if(d[i][j] > 1)add(id(i, j), id(i + d[i][j] - 1, j), dis);
		}
	}
	dijkstra();
	if(dis[T] == 0x3f3f3f3f)puts("nemoguce");
	else printf("%d\n", dis[T]);
	return 0;
}
