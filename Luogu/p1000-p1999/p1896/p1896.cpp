#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
int n, k;
int sit[N], sta[N];
long long f[12][N][110];
int idx = 0;
void dfs(int p, int num, int cur)
{
	if(cur >= n)
	{
		idx++;
		sit[idx] = p;
		sta[idx] = num;
		return;
	}
	dfs(p, num, cur + 1);
	dfs(p + (1 << cur), num + 1, cur + 2);
	return;
}
int main()
{
	cin >> n >> k;
	dfs(0, 0, 0);
	for(int i = 1; i <= idx; i++)f[1][i][sta[i]] = 1;
	for(int i = 2; i <= n; i++)
	{
		for(int j = 1; j <= idx; j++)
		{
			for(int x = 1; x <= idx; x++)
			{
				if(sit[j] & sit[x])continue;
				if((sit[j] << 1) & sit[x])continue;
				if(sit[j] & (sit[x] << 1))continue;
				for(int s = k; s >= sta[j]; s--)
				{
					f[i][j][s] += f[i - 1][x][s - sta[j]];
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 1; i <= idx; i++)
	{
		ans += f[n][i][k];
	}
	cout << ans << endl;
	return 0;
}
