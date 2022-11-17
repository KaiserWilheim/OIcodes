#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 510;
struct Node
{
	int x, y, dis;
	Node(int _x, int _y, int _d) { x = _x, y = _y, dis = _d; }
	bool operator < (const Node &rhs)const
	{
		return dis > rhs.dis;
	}
};
int n, m;
char buf[N];
int st[N][N];
int dis[N][N];
bool vis[N][N];
int X[5] = { 1,1,-1,-1 }, Y[5] = { 1,-1,-1,1 };
bool chq(int x, int y)
{
	if(x < 0)return false;
	if(x > n)return false;
	if(y < 0)return false;
	if(y > m)return false;
	return true;
}
int calc(int x, int y, int d)
{
	if(d == 0)return st[x + 1][y + 1] == 1;
	if(d == 1)return st[x + 1][y] == 0;
	if(d == 2)return st[x][y] == 1;
	if(d == 3)return st[x][y + 1] == 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	if(n % 2 != m % 2)
	{
		puts("NO SOLUTION");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf + 1);
		for(int j = 1; j <= m; j++)
			st[i][j] = (buf[j] == '/');
	}
	memset(dis, 63, sizeof(dis));
	dis[0][0] = 0;
	priority_queue<Node>q;
	q.emplace(0, 0, 0);
	while(!q.empty())
	{
		Node now = q.top();
		q.pop();
		if(vis[now.x][now.y])continue;
		vis[now.x][now.y] = true;
		for(int i = 0; i < 4; i++)
		{
			int nx = now.x + X[i], ny = now.y + Y[i];
			if(!chq(nx, ny))continue;
			int w = calc(now.x, now.y, i);
			if(dis[nx][ny] > dis[now.x][now.y] + w)
			{
				dis[nx][ny] = dis[now.x][now.y] + w;
				q.emplace(nx, ny, dis[nx][ny]);
			}
		}
	}
	printf("%d\n", dis[n][m]);
	return 0;
}
