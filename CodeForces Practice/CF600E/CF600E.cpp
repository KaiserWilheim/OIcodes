#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 200010;
int n;
int col[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int sz[N], son[N];
void dfs1(int p, int fa)
{
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
int cnt[N];
ll ans[N];
int maxn; ll sum;
void add(int p)
{
	cnt[col[p]]++;
	if(cnt[col[p]] > maxn)
	{
		maxn = cnt[col[p]];
		sum = col[p];
	}
	else if(cnt[col[p]] == maxn)
		sum += col[p];
}
void dfs2(int p, int fa, int flag)
{
	if(!son[p])
	{
		ans[p] = col[p];
		if(flag)add(p);
		else cnt[col[p]] = maxn = sum = 0;
		return;
	}
	if(flag == 2)
	{
		add(p);
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(e[i] == fa)continue;
			dfs2(e[i], p, 2);
		}
		return;
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || e[i] == son[p])continue;
		dfs2(e[i], p, 0);
	}
	dfs2(son[p], p, 1);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || e[i] == son[p])continue;
		dfs2(e[i], p, 2);
	}
	add(p);
	ans[p] = sum;
	if(!flag)
	{
		maxn = sum = 0;
		for(int i = 1; i <= n; i++)
			cnt[i] = 0;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 0, 1);
	for(int i = 1; i <= n; i++)
		printf("%lld ", ans[i]);
	putchar('\n');
	return 0;
}
