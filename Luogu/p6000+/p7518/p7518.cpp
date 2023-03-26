#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m, c, q;
int col[N];
int pla[N];
int pre[N], suf[N], pos[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int now[N];
int up[N][24], up1[N];
int fa[N], dep[N], son[N], sz[N], top[N];
void dfs1(int p, int fa)
{
	if(now[suf[col[p]]])up[p][0] = now[suf[col[p]]];
	for(int i = 1; i < 21; i++)up[p][i] = up[up[p][i - 1]][i - 1];
	int tmp = now[col[p]];
	now[col[p]] = p;
	if(now[pla[1]])up1[p] = now[pla[1]];
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
	now[col[p]] = tmp;
}
void dfs2(int p, int t)
{
	top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
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
struct DSU
{
	int fa[N], sz[N], rt[N], col[N];
	int find(int p)
	{
		return p == fa[p] ? p : find(fa[p]);
	}
};
DSU dsu;
int ans[N];
vector<int>qc[N], qn[N], qid[N];
void dfs3(int p)
{
	for(int i = 0; i < qc[p].size(); i++)
	{
		int c = qc[p][i], t = qid[p][i];
		dsu.fa[t] = t, dsu.sz[t] = 1, dsu.col[t] = c;
		if(dsu.rt[c])
		{
			dsu.fa[t] = dsu.rt[c];
			dsu.sz[dsu.rt[c]]++;
		}
		else dsu.rt[c] = t;
	}
	int u = dsu.rt[col[p]];
	dsu.rt[col[p]] = 0;
	int c = suf[col[p]], v = dsu.rt[c];
	if(u)
	{
		if(!v)dsu.rt[c] = u, dsu.col[u] = c;
		else if(dsu.sz[u] < dsu.sz[v])dsu.fa[u] = v, dsu.sz[v] += dsu.sz[u];
		else dsu.fa[v] = dsu.rt[c] = u, dsu.sz[u] += dsu.sz[v], dsu.col[u] = c;
	}
	for(int i = 0; i < qn[p].size(); i++)
	{
		int t = dsu.col[dsu.find(qn[p][i])];
		ans[qn[p][i]] = t ? pos[t] - 1 : ::c;
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p])continue;
		dfs3(e[i]);
	}
	if(u)
	{
		if(!v)dsu.rt[c] = 0, dsu.col[u] = col[p];
		else if(dsu.rt[c] == v)dsu.fa[u] = u, dsu.sz[v] -= dsu.sz[u];
		else dsu.fa[v] = dsu.rt[c] = v, dsu.sz[u] -= dsu.sz[v], dsu.col[u] = col[p];
	}
	dsu.rt[col[p]] = u;
	for(int i = 0; i < qc[p].size(); i++)
	{
		int c = qc[p][i], t = qid[p][i];
		if(dsu.rt[c] == t)dsu.rt[c] = 0;
		else dsu.sz[dsu.fa[t]]--;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &c);
	for(int i = 1; i <= c; i++)
		scanf("%d", &pla[i]);
	for(int i = 1; i <= c; i++)
	{
		pre[pla[i]] = pla[i - 1];
		suf[pla[i]] = pla[i + 1];
		pos[pla[i]] = i;
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int g = lca(u, v);
		if(dep[up1[u]] <= dep[g])
		{
			qc[g].push_back(pla[1]);
			qid[g].push_back(i);
			qn[v].push_back(i);
		}
		else
		{
			int tmp = up1[u];
			for(int j = 20; j >= 0; j--)
				if(dep[up[tmp][j]] > dep[g])tmp = up[tmp][j];
			tmp = col[tmp];
			if(suf[tmp])
			{
				qc[g].push_back(suf[tmp]);
				qid[g].push_back(i);
				qn[v].push_back(i);
			}
			else ans[i] = m;
		}
	}
	dfs3(1);
	for(int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
