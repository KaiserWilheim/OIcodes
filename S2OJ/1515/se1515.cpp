#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int fa[N], dep[N];
int top[N];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs(e[i], p, depth + 1);
		top[e[i]] = w[i];
	}
}
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
struct Edge
{
	int id, u, v, c;
};
Edge E[N];
int ans[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		E[i] = { i,u,v,c };
		if(c)add(u, v, i), add(v, u, i);
	}
	for(int i = 1; i <= n; i++)p[i] = i;
	dfs(1, 0, 1);
	int last = 0;
	for(int i = 1; i <= m; i++)
	{
		vector<int>cyc;
		int u = E[i].u, v = E[i].v;
		while(find(u) != find(v))
		{
			if(dep[find(u)] < dep[find(v)])swap(u, v);
			u = find(u);
			p[u] = find(fa[u]);
			cyc.push_back(top[u]);
		}
		sort(cyc.begin(), cyc.end());
		for(auto j : cyc)
			ans[j] = ++last;
		if(!E[i].c)ans[i] = ++last;
	}
	for(int i = 1; i <= m; i++)
	{
		if(!ans[i])ans[i] = ++last;
		printf("%d ", ans[i]);
	}
	putchar('\n');
	return 0;
}