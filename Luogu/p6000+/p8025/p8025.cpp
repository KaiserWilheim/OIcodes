#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N], fa[N], sz[N], son[N];
int id[N], nw[N], top[N], cnt;
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[j] > sz[son[p]])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = p, top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p])continue;
		dfs2(j, j);
	}
}
int lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
int jump(int p, int k)
{
	while(dep[p] - dep[top[p]] + 1 <= k)
	{
		k -= dep[p] - dep[top[p]] + 1;
		p = fa[top[p]];
	}
	return nw[id[p] - k];
}
int main()
{
	memset(h, -1, sizeof(h));
	int u;
	scanf("%d%d%d", &n, &u, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	while(m--)
	{
		int v, step;
		scanf("%d%d", &v, &step);
		int x = lca(u, v);
		int dis1 = dep[u] - dep[x], dis2 = dep[v] - dep[x];
		if(step >= dis1 + dis2)
		{
			u = v;
			printf("%d ", u);
		}
		else if(step == dis1)
		{
			u = x;
			printf("%d ", u);
		}
		else if(step < dis1)
		{
			u = jump(u, step);
			printf("%d ", u);
		}
		else
		{
			u = jump(v, dis2 - (step - dis1));
			printf("%d ", u);
		}
	}
	return 0;
}
