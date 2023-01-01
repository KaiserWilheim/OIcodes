#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int type;
int n, m;
vector<int>path[N];
int fa[N][20], dep[N];
int su[N], sv[N];
struct DSU
{
	int p[N], sz[N];
	void init(int n)
	{
		for(int i = 0; i <= n; i++)
			p[i] = i, sz[i] = 1;
	}
	int find(int x)
	{
		if(p[x] != x)p[x] = find(p[x]);
		return p[x];
	}
};
DSU dsu;
void dfs(int p, int father)
{
	dep[p] = dep[father] + 1;
	fa[p][0] = father;
	for(int k = 1; k <= 18; k++)
		fa[p][k] = fa[fa[p][k - 1]][k - 1];
	for(auto v : path[p])
	{
		if(v == father)continue;
		dfs(v, p);
	}
}
int __lca(int p, int q)
{
	if(dep[p] < dep[q])swap(p, q);
	for(int i = 18; ~i; i--)
		if(dep[fa[p][i]] >= dep[q])
			p = fa[p][i];
	if(p == q)return p;
	for(int i = 18; ~i; i--)
		if(fa[p][i] != fa[q][i])
			p = fa[p][i], q = fa[q][i];
	return fa[p][0];
}
int getdis(int u, int v)
{
	return dep[u] + dep[v] - 2 * dep[__lca(u, v)];
}
int main()
{
	scanf("%d", &type);
	scanf("%d%d", &n, &m);
	int lans = 0;
	for(int i = 1; i <= n; i++)
		su[i] = sv[i] = i;
	dsu.init(n);
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u ^= lans * type, v ^= lans * type;
			int fu = dsu.find(u), fv = dsu.find(v);
			if(dsu.sz[fu] < dsu.sz[fv])swap(fu, fv), swap(u, v);
			path[u].push_back(v);
			path[v].push_back(u);
			dfs(v, u);
			int ansu = su[fu], ansv = sv[fu];
			int dis = getdis(ansu, ansv);
			if(getdis(su[fv], sv[fv]) > dis)
			{
				ansu = su[fv], ansv = sv[fv];
				dis = getdis(ansu, ansv);
			}
			if(getdis(su[fu], su[fv]) > dis)
			{
				ansu = su[fu], ansv = su[fv];
				dis = getdis(ansu, ansv);
			}
			if(getdis(sv[fu], sv[fv]) > dis)
			{
				ansu = sv[fu], ansv = sv[fv];
				dis = getdis(ansu, ansv);
			}
			if(getdis(su[fu], sv[fv]) > dis)
			{
				ansu = su[fu], ansv = sv[fv];
				dis = getdis(ansu, ansv);
			}
			if(getdis(sv[fu], su[fv]) > dis)
			{
				ansu = sv[fu], ansv = su[fv];
				dis = getdis(ansu, ansv);
			}
			su[fu] = ansu, sv[fu] = ansv;
			dsu.p[fv] = fu;
			dsu.sz[fu] += dsu.sz[fv];
		}
		else
		{
			int x;
			scanf("%d", &x);
			x ^= lans * type;
			lans = max(getdis(x, su[dsu.find(x)]), getdis(x, sv[dsu.find(x)]));
			printf("%d\n", lans);
		}
	}
	return 0;
}