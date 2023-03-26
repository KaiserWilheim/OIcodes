#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010;
int n, m, q;
vector<int>e[N], re[N];
vector<int>ov[N];
bool flag[N][N], rflag[N][N];
bool gflag[N];
void dfs1(int p, int t)
{
	flag[p][t] = true;
	if(p == t)return;
	for(auto i : e[p])
	{
		if(!flag[i][t])dfs1(i, t);
	}
}
void dfs2(int p, int t, int id)
{
	if(p == id)return;
	rflag[p][t] = true;
	for(auto i : re[p])
	{
		if(!rflag[i][t])dfs2(i, t, id);
	}
}
int tmp[N], fa[N];
bool cmp(int a, int b) { return ov[a].size() < ov[b].size(); }
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		re[v].push_back(u);
	}
	dfs1(1, 0);
	for(int i = 1; i <= n; i++)tmp[i] = i;
	for(int i = 1; i <= n; i++)
	{
		dfs1(1, i);
		for(int j = 1; j <= n; j++)
			if(flag[j][0] && !flag[j][i])
				ov[j].push_back(i);
	}
	sort(tmp + 1, tmp + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		for(auto j : ov[i])
		{
			if(ov[j].size() == ov[i].size() - 1)
			{
				fa[i] = j;
				break;
			}
		}
	}
	for(int i = 2; i <= n; i++)
		dfs2(i, i, fa[i]);
	while(q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int ans = 0;
		for(int i = 1; i <= n; i++)
			if(flag[u][fa[i]] && rflag[v][i] && fa[i] != 1 && fa[i] != u)gflag[i] = true;
		for(int i = 1; i <= n; i++)
			if(gflag[fa[tmp[i]]])gflag[tmp[i]] = true;
		for(int i = 1; i <= n; i++)
			if(gflag[i])ans++, gflag[i] = false;
		printf("%d\n", ans);
	}
	return 0;
}
