#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 500010, M = N << 1;
struct Trie
{
	struct Node
	{
		int s[2];
		int end;
	};
	Node tr[N * 60];
	int idx;
	void clear()
	{
		for(int i = 0; i <= idx; i++)
			tr[i].s[0] = tr[i].s[1] = tr[i].end = 0;
		idx = 0;
	}
	void insert(ll x, int id)
	{
		int p = 0;
		for(int i = 59; i >= 0; i--)
		{
			int c = (x >> i) & 1;
			if(!tr[p].s[c])tr[p].s[c] = ++idx;
			p = tr[p].s[c];
		}
		tr[p].end = id;
	}
	int query(ll x)
	{
		int p = 0;
		for(int i = 59; i >= 0; i--)
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
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll a[N], ans[N];
Trie tr;
int l1, l2; ll maxn;
int dep[N], fa[N];
bool tag[N];
void dfs1(int p, int fa)
{
	dep[p] = dep[fa] + 1, ::fa[p] = fa;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 2; i <= n; i++)
	{
		int fa;
		scanf("%d", &fa);
		add(i, fa), add(fa, i);
	}
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	tr.clear();
	for(int i = 1; i <= n; i++)
	{
		tr.insert(a[i], i);
		int j = tr.query(a[i]);
		if((a[i] ^ a[j]) > maxn)l1 = j, l2 = i, maxn = a[i] ^ a[j];
	}
	dfs1(1, 0);
	int g = lca(l1, l2);
	for(int i = g; i >= 1; i = fa[i])tag[i] = true;
	for(int i = 2; i <= n; i++)
		if(!tag[i])ans[i] = maxn;
	solve(1, l1);
	solve(g, l2);
	for(int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
