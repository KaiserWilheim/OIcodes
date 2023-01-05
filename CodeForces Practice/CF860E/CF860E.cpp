#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
vector<int>v[N];
int dep[N], son[N], lval[N];
ll ans[N];
vector<pair<int, int>>g[N];
void dfs1(int p)
{
	for(int i : v[p])
	{
		dep[i] = dep[p] + 1;
		dfs1(i);
		if(lval[p] < lval[i] + 1)son[p] = i, lval[p] = lval[i] + 1;
	}
}
void dfs2(int p)
{
	if(son[p])dfs2(son[p]), h[p] = h[son[p]];
	for(int i : v[p])
	{
		if(i == son[p])continue;
		dfs2(i);
		int j = h[p], k = h[i];
		while(~k)
		{
			ans[w[k]] += dep[p] * e[j];
			ans[w[j]] += dep[p] * e[k];
			g[w[j]].emplace_back(w[k], ans[w[k]] - ans[w[j]]);
			e[j] += e[k];
			j = ne[j], k = ne[k];
		}
	}
	add(p, 1, p);
}
void dfs3(int p, bool rt = 1)
{
	if(rt && son[p])dfs3(son[p]);
	for(auto i : g[p])
	{
		ans[i.first] = ans[p] + i.second;
		dfs3(i.first, 0);
	}
}
void dfs4(int p)
{
	for(int i : v[p])
	{
		ans[i] += dep[p] + ans[p];
		dfs4(i);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	int rt;
	for(int i = 1; i <= n; i++)
	{
		int fa;
		scanf("%d", &fa);
		if(fa)v[fa].push_back(i);
		else rt = i;
	}
	dep[rt] = 1;
	dfs1(rt);
	dfs2(rt);
	dfs3(rt);
	dfs4(rt);
	for(int i = 1; i <= n; i++)
		printf("%lld ", ans[i]);
	putchar('\n');
	return 0;
}
