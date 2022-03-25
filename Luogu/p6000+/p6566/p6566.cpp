#include<bits/stdc++.h>
const int N = 2010;
using namespace std;
int n, m;
int dx[8] = { 0,0,1,1,1,-1,-1,-1 };
int dy[8] = { 1,-1,1,0,-1,1,0,-1 };
int galaxy[N * N], sum, Max;
bool star[N][N];
void Search(int x, int y)
{
	sum++;
	star[x][y] = false;
	for(int i = 0; i < 8; i++)
	{
		int xx = x + dx[i], yy = y + dy[i];
		if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && star[xx][yy])
			Search(xx, yy);
	}
}
int main()
{
	//freopen("star.in", "r", stdin);
	//freopen("star.out", "w", stdout);
	char c;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			cin >> c;
			if(c == '*')star[i][j] = true;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(star[i][j])
			{
				Search(i, j);
				galaxy[sum]++;
				if(sum * galaxy[sum] > Max)Max = sum * galaxy[sum];
				sum = 0;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= n * m; i++)
	{
		if(galaxy[i])ans++;
	}
	cout << ans << ' ' << Max;
	return 0;
}
