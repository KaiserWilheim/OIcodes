#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
#define lowbit(i) ((i)&-(i))
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], dep[N], sz[N], son[N], top[N];
int dfn[N], tot;
void dfs1(int p, int father, int depth)
{
	fa[p] = father, dep[p] = depth, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs1(e[i], p, depth + 1);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	dfn[p] = ++tot, top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
}
int __lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
int getson(int p, int q)
{
	while(top[p] != top[q])
	{
		if(fa[top[p]] == q)return top[p];
		p = fa[top[p]];
	}
	return son[q];
}
int c[N];
void segadd(int x, int v)
{
	for(int i = x; i <= n; i += lowbit(i))
		c[i] += v;
}
int segsum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += c[i];
	return res;
}
struct Query
{
	int op, x, l, r, k, v, id;
	bool operator < (const Query &rhs)const
	{
		return x == rhs.x ? op < rhs.op : x < rhs.x;
	}
};
Query q[M], q1[M], q2[M];
int Q, cnt;
int dic[M];
int ans[M];
void solve(int ql, int qr, int l, int r)
{
	if(ql > qr)return;
	if(l == r)
	{
		for(int i = ql; i <= qr; i++)
			if(q[i].op == 2)ans[q[i].id] = dic[l];
		return;
	}
	int tt1 = 0, tt2 = 0;
	int mid = (l + r) >> 1;
	for(int i = ql; i <= qr; i++)
	{
		if(q[i].op == 1)
		{
			if(q[i].k <= mid)
			{
				segadd(q[i].l, q[i].v);
				segadd(q[i].r + 1, -q[i].v);
				q1[++tt1] = q[i];
			}
			else q2[++tt2] = q[i];
		}
		else
		{
			int tmp = segsum(q[i].l);
			if(tmp >= q[i].k)
			{
				q1[++tt1] = q[i];
			}
			else
			{
				q[i].k -= tmp;
				q2[++tt2] = q[i];
			}
		}
	}
	for(int i = 1; i <= tt1; i++)q[ql + i - 1] = q1[i];
	for(int i = 1; i <= tt2; i++)q[ql + i + tt1 - 1] = q2[i];
	solve(ql, ql + tt1 - 1, l, mid);
	solve(ql + tt1, qr, mid + 1, r);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for(int i = 1; i <= m; i++)
	{
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		dic[i] = k;
		if(dfn[x] > dfn[y])swap(x, y);
		int lca = __lca(x, y);
		if(lca == x)
		{
			int z = getson(y, x);
			if(dfn[z] > 1)
			{
				q[++cnt] = { 1,1,dfn[y],dfn[y] + sz[y] - 1,k,1,0 };
				q[++cnt] = { 1,dfn[z],dfn[y],dfn[y] + sz[y] - 1,k,-1,0 };
			}
			if(dfn[z] + sz[z] - 1 < n)
			{
				q[++cnt] = { 1,dfn[y],dfn[z] + sz[z],n,k,1,0 };
				q[++cnt] = { 1,dfn[y] + sz[y],dfn[z] + sz[z],n,k,-1,0 };
			}
		}
		else
		{
			q[++cnt] = { 1,dfn[x],dfn[y],dfn[y] + sz[y] - 1,k,1,0 };
			q[++cnt] = { 1,dfn[x] + sz[x],dfn[y],dfn[y] + sz[y] - 1,k,-1,0 };
		}
	}
	sort(dic + 1, dic + 1 + m);
	int lim = unique(dic + 1, dic + 1 + m) - dic - 1;
	for(int i = 1; i <= cnt; i++)
		q[i].k = lower_bound(dic + 1, dic + 1 + lim, q[i].k) - dic;
	for(int i = 1; i <= Q; i++)
	{
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		if(dfn[x] > dfn[y])swap(x, y);
		q[++cnt] = { 2,dfn[x],dfn[y],0,k,0,i };
	}
	sort(q + 1, q + 1 + cnt);
	solve(1, cnt, 1, lim);
	for(int i = 1; i <= Q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
