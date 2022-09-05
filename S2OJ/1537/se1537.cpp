#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010, M = N << 1;
int n, m;
int vis[N][N], dis[N][N];
bool hab[N][N];
int X[4] = { 1,0,-1,0 }, Y[4] = { 0,1,0,-1 };
struct step
{
	int x, y;
	step(int _x, int _y) :x(_x), y(_y) {}
};
queue<step>q;
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	int k;
	cin >> k;
	for(int i = 1; i <= k; i++)
	{
		int x, y;
		cin >> x >> y;
		vis[x][y] = i;
		dis[x][y] = 0;
		q.emplace(x, y);
	}
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		int x, y;
		cin >> x >> y;
		hab[x][y] = true;
	}
	while(!q.empty())
	{
		step p = q.front();
		q.pop();
		int x = p.x, y = p.y;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + X[i], ny = y + Y[i];
			if(nx > n || nx < 1 || ny > m || ny < 1)continue;
			if(!hab[nx][ny])
			{
				if(!vis[nx][ny])
				{
					dis[nx][ny] = dis[x][y] + 1;
					vis[nx][ny] = vis[x][y];
					q.emplace(nx, ny);
				}
				else if(dis[nx][ny] == dis[x][y] + 1 && vis[nx][ny] != vis[x][y])
					vis[nx][ny] = -1;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(vis[i][j] == -1)ans++;
	cout << ans << endl;
	return 0;
}