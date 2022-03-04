#include<bits/stdc++.h>
using namespace std;
vector<int> e[20005], w[20005];
int n, dis[20005], p[20005], ans, len;
void dfs(int x, int fa)
{
	for(int i = 0; i < e[x].size(); i++)
	{
		int y = e[x][i];
		if(y != fa)
		{
			p[y] = w[x][i];
			dfs(y, x);
			dis[x] = max(dis[x], dis[y] + w[x][i]);
		}
	}
	if(dis[x] + p[x] >= len)
	{
		ans++;
		dis[x] = 0;
	}
}
int main()
{
	scanf("%d", &n);
	int maxn = 0, b, k;
	for(int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);
		for(int j = 1; j <= m; j++)
		{
			scanf("%d%d", &b, &k);
			e[i].push_back(b);
			w[i].push_back(k);
			maxn = max(maxn, k);
		}
	}
	scanf("%d", &len);
    if(maxn >= len){
		puts("No solution.");
        return 0;
    }
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
