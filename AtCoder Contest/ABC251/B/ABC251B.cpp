#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n, m;
int w[N];
bool vis[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
		if(w[i] <= m)vis[w[i]] = true;
	}
	if(n == 1)
	{
		if(w[1] <= m)puts("1");
		return 0;
	}
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			if(w[i] + w[j] <= m)
				vis[w[i] + w[j]] = true;
	if(n == 2)
	{
		int ans = 0;
		for(int i = 1; i <= m; i++)
			if(vis[i])ans++;
		printf("%d\n", ans);
		return 0;
	}
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			for(int k = j + 1; k <= n; k++)
				if(w[i] + w[j] + w[k] <= m)
					vis[w[i] + w[j] + w[k]] = true;
	int ans = 0;
	for(int i = 1; i <= m; i++)
		if(vis[i])ans++;
	printf("%d\n", ans);
	return 0;
}
