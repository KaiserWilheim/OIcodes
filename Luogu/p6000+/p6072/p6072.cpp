#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 30010, M = N << 1;
struct Trie
{
	struct Node
	{
		int s[2];
		int end;
	};
	Node tr[N * 30];
	int idx;
	void clear()
	{
		for(int i = 0; i <= idx; i++)
			tr[i].s[0] = tr[i].s[1] = tr[i].end = 0;
		idx = 0;
	}
	void insert(int x, int id)
	{
		int p = 0;
		for(int i = 29; i >= 0; i--)
		{
			int c = (x >> i) & 1;
			if(!tr[p].s[c])tr[p].s[c] = ++idx;
			p = tr[p].s[c];
		}
		tr[p].end = id;
	}
	int query(int x)
	{
		int p = 0;
		for(int i = 29; i >= 0; i--)
		{
			int c = (x >> i) & 1;
			if(tr[p].s[c ^ 1])p = tr[p].s[c ^ 1];
			else if(tr[p].s[c])p = tr[p].s[c];
			else return 0;
		}
		return tr[p].end;
	}
};

int n;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
int a[N], ans[N];
Trie tr;
int l1, l2; int maxn;
int dep[N], fa[N], deg[N];
bool tag[N];
void dfs1(int p, int fa, int v)
{
	dep[p] = dep[fa] + 1, ::fa[p] = fa, a[p] = v;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p, v ^ w[i]);
	}
}
int lca(int p, int q)
{
	if(dep[p] < dep[q])swap(p, q);
	tag[p] = tag[q] = true;
	while(dep[p] > dep[q])p = fa[p], tag[p] = true;
	if(p == q)return p;
	while(p != q)p = fa[p], q = fa[q], tag[p] = tag[q] = true;
	return p;
}
int sta[N], tt;
bool vis[N];
void dfs2(int p, int fa)
{
	tr.insert(a[p], p);
	int q = tr.query(a[p]);
	if((a[p] ^ a[q]) > maxn)maxn = a[p] ^ a[q];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		dfs2(e[i], p);
	}
}
void solve(int p, int q)
{
	if(p == q)return;
	if(dep[p] < dep[q])swap(p, q);
	tt = 0;
	while(p != q)sta[++tt] = p, vis[p] = true, p = fa[p];
	tr.clear(), maxn = 0;
	dfs2(1, 0);
	for(int i = tt; i; i--)
	{
		ans[sta[i]] = maxn;
		dfs2(sta[i], fa[sta[i]]);
		vis[sta[i]] = false;
	}
}
int res = 0;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	bool flag = true;
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
		deg[u]++, deg[v]++;
		if(deg[u] > 2 || deg[v] > 2)flag = false;
	}
	dfs1(1, 0, 0);
	tr.clear(), maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		tr.insert(a[i], i);
		int j = tr.query(a[i]);
		if((a[i] ^ a[j]) > maxn)l1 = j, l2 = i, maxn = a[i] ^ a[j];
	}
	int g = lca(l1, l2);
	for(int i = g; i >= 1; i = fa[i])tag[i] = true;
	for(int i = 2; i <= n; i++)
		if(!tag[i])ans[i] = maxn;
	solve(1, l1), solve(g, l2);
	if(flag && deg[l1] == 1 && deg[l2] == 1)
	{
		tr.clear(), maxn = 0;
		if(deg[l2] < deg[l1])swap(l1, l2);
		for(int i = l2; i != l1; i = fa[i])
		{
			tr.insert(a[i], i);
			int j = tr.query(a[i]);
			if((a[i] ^ a[j]) > maxn)maxn = a[i] ^ a[j];
			res = max(res, ans[i] + maxn);
		}
		printf("%d\n", res);
		return 0;
	}

	for(int i = g; i >= 1; i = fa[i])
		res = max(res, ans[i] + (a[l1] ^ a[l2]));

	queue<int>q;
	for(int i = l1; i != g; i = fa[i])
	{
		for(int j = h[i]; ~j; j = ne[j])
			if(!tag[e[j]])q.push(e[j]);
	}
	for(int i = l2; i != g; i = fa[i])
	{
		for(int j = h[i]; ~j; j = ne[j])
			if(!tag[e[j]])q.push(e[j]);
	}
	for(int i = h[g]; ~i; i = ne[i])
		if(!tag[e[i]])q.push(e[i]);
	for(int i = 1; i <= n; i++)vis[i] = false;
	while(!q.empty())
	{
		tr.clear(), maxn = 0;
		dfs2(q.front(), fa[q.front()]);
		res = max(res, maxn + (a[l1] ^ a[l2]));
		q.pop();
	}
	res = max(res, maxn + (a[l1] ^ a[l2]));

	tr.clear(), maxn = 0;
	for(int i = 1; i <= n; i++)vis[i] = false;
	for(int i = l1; i != fa[g]; i = fa[i])
	{
		dfs2(i, fa[i]);
		vis[i] = true;
		res = max(res, maxn + ans[i]);
	}
	tr.clear(), maxn = 0;
	for(int i = 1; i <= n; i++)vis[i] = false;
	for(int i = l2; i != fa[g]; i = fa[i])
	{
		dfs2(i, fa[i]);
		vis[i] = true;
		res = max(res, maxn + ans[i]);
	}

	printf("%d\n", res);
	return 0;
}
