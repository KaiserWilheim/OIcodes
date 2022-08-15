#include<bits/stdc++.h>
using namespace std;
int reich[20][20];
bool vis[30];
int idx = 0;
int ans = 0;
int n;
void dfs(int p, int now)
{
	while(vis[p])p++;
	if(p == 2 * n + 1)
	{
		ans = max(ans, now);
		return;
	}
	for(int i = p + 1; i <= 2 * n; i++)
	{
		if(!vis[i])
		{
			vis[i] = true;
			dfs(p + 1, now ^ reich[i][p]);
			vis[i] = false;
		}
	}
	return;
}
int main()
{
	cin >> n;
	for(int i = 1; i <= 2 * n - 1; i++)
	{
		for(int j = i + 1; j <= 2 * n; j++)
		{
			scanf("%d", &reich[i][j]);
			reich[j][i] = reich[i][j];
		}
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
