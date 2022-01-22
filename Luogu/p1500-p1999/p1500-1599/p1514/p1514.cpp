#include<bits/stdc++.h>
const int MAXN = 1010;
using namespace std;
int n, m;
int dx[5] = { -1, 0, 1, 0 };
int dy[5] = { 0, 1, 0, -1 };
int vis[MAXN][MAXN];
int h[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN];
void dfs(int x, int y)
{
	vis[x][y] = 1;
	for(int i = 0; i < 4; i++)
	{
		int x1 = x + dx[i];
		int y1 = y + dy[i];
		if(x1 < 1 || x1 > n || y1 < 1 || y1 > m || h[x][y] <= h[x1][y1]) continue;
		if(!vis[x1][y1]) dfs(x1, y1);
		l[x][y] = min(l[x][y], l[x1][y1]);
		r[x][y] = max(r[x][y], r[x1][y1]);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(l, 2100000, sizeof(l));
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &h[i][j]);
			if(i == n)
			{
				l[i][j] = j;
				r[i][j] = j;
			}
		}
	}
	for(int i = 1; i <= m; i++)
	{
		if(!vis[1][i]) dfs(1, i);
	}
	bool chq = true;
	int ans = 0;
	for(int i = 1; i <= m; i++)
	{
		if(!vis[n][i])
		{
			chq = false;
			ans++;
		}
	}
	if(!chq)
	{
		cout << 0 << endl << ans << endl;
		return 0;
	}
	int left = 1, right = r[1][1];
	while(left <= m)
	{
		for(int i = 1; i <= m; i++)
		{
			if(l[1][i] <= left)
			{
				right = max(right, r[1][i]);
			}
		}

		left = right + 1;
		ans++;
	}
	cout << 1 << endl << ans << endl;
	return 0;
}
