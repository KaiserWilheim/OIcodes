#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
int n, m;
int g[N][N];
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int sc;
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(int i = 1; i <= n; i++)
	{
		if(g[p][i] == 0)continue;
		if(!dfn[i])
		{
			tarjan(i);
			low[p] = min(low[p], low[i]);
		}
		else if(vis[i])
		{
			low[p] = min(low[p], dfn[i]);
		}
	}
	if(dfn[p] == low[p])
	{
		++sc;
		while(sta[tt] != p)
		{
			vis[sta[tt]] = false;
			tt--;
		}
		vis[sta[tt]] = false;
		tt--;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	if(sc > 1)puts("NO");
	else puts("YES");
	return 0;
}