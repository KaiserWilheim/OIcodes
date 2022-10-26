#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 510;
struct Node
{
	int x, y, d;
};
int n, p;
int vis[N][N][5];
int dis[N][N][5];
char s[N][N];
int a[N][N];
int dx[5] = { 0, 0, 1, 0, -1 }, dy[5] = { 0, 1, 0, -1, 0 };
int bfs()
{
	memset(dis, 0x3f, sizeof dis);
	memset(vis, false, sizeof vis);
	dis[1][1][a[1][1]] = 0;
	deque<Node> q;
	q.push_front({ 1, 1, a[1][1] });

	while(q.size())
	{
		auto t = q.front();
		q.pop_front();
		int x = t.x, y = t.y, d = t.d;
		if(vis[x][y][d]) continue;
		vis[x][y][d] = true;
		if(dis[x + dx[d]][y + dy[d]][a[x + dx[d]][y + dy[d]]] > dis[x][y][d])
		{
			dis[x + dx[d]][y + dy[d]][a[x + dx[d]][y + dy[d]]] = dis[x][y][d];
			q.push_front({ x + dx[d], y + dy[d], a[x + dx[d]][y + dy[d]] });
		}
		if(dis[x][y][(d % 4) + 1] > dis[x][y][d] + 1 && d)
		{
			dis[x][y][(d % 4) + 1] = dis[x][y][d] + 1;
			q.push_back({ x, y, (d % 4) + 1 });
		}
	}

	if(dis[n][p][0] == 0x3f3f3f3f) return -1;
	return dis[n][p][0];
}
int main()
{
	cin >> n >> p;
	for(int i = 1; i <= n; ++i)
	{
		cin >> s[i] + 1;
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= p; ++j)
		{
			if(s[i][j] == 'E') a[i][j] = 1;
			else if(s[i][j] == 'S') a[i][j] = 2;
			else if(s[i][j] == 'W') a[i][j] = 3;
			else if(s[i][j] == 'N') a[i][j] = 4;
		}
	}
	cout << bfs() << endl;
	return 0;
}