#include<bits/stdc++.h>
using namespace std;
const int N = 110;
char land[N][N];
bool vis[N][N];
int n, m, ans = 0;
void bfs(int i, int j)
{
	if(i < 0)return;
	if(i >= n)return;
	if(j < 0)return;
	if(j >= m)return;
	vis[i][j] = true;
	if((land[i+1][j] != '0') && (!vis[i+1][j]))bfs(i+1, j);
	if((land[i-1][j] != '0') && (!vis[i-1][j]))bfs(i-1, j);
	if((land[i][j+1] != '0') && (!vis[i][j+1]))bfs(i, j+1);
	if((land[i][j-1] != '0') && (!vis[i][j-1]))bfs(i, j-1);
	return;
}
int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)
	{
		cin >> land[i];
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if((land[i][j] != '0') && (!vis[i][j]))
			{
				bfs(i, j);
				ans++;
			}
		}
	}
	cout << ans << endl;
}
