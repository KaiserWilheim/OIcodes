#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int w[N];
int ans[M];
int col[N];
int fa[N], id[N];
int pos[N];
bool cmp1(int l, int r)
{
	return w[l] < w[r];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		pos[i] = i;
		scanf("%d", &w[i]);
	}
	sort(pos + 1, pos + 1 + n, cmp1);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(w[u] == w[v])
		{
			if(!col[u] && !col[v])
				col[u] = 2;
			if(!col[u])
				col[u] = col[v] ^ 1;
			if(!col[v])
				col[v] = col[u] ^ 1;
			if((col[u] ^ col[v]) == 1)
				ans[i] = w[u];
		}
		else
		{
			if(w[u] < w[v])swap(u, v);
			fa[u] = v;
			id[u] = i;
		}
	}
	for(int _i = 1; _i <= n; _i++)
	{
		int i = pos[_i];
		if(!col[i])
		{
			if(!fa[i])
			{
				puts("-1");
				return 0;
			}
			col[i] = col[fa[i]];
			ans[id[i]] = w[i] - w[fa[i]];
		}
	}
	for(int i = 1; i <= n; i++)
		putchar(col[i] == 2 ? 'B' : 'W');
	putchar('\n');
	for(int i = 1; i <= m; i++)
	{
		if(!ans[i])ans[i] = 1e9;
		printf("%d\n", ans[i]);
	}
	return 0;
}
