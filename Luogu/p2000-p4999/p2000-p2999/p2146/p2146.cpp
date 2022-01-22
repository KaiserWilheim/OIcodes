#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
int id[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct segtree
{
	int l, r;
	ll add, sum;
}tr[N << 3];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father) continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j]) son[p] = j;
	}
	return;
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, top[p] = t;
	if(!son[p]) return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
	return;
}
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	return;
}
void pushdown(int p)
{
	auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
	if(root.add!=-1)
	{
		left.add = root.add, left.sum = root.add * (left.r - left.l + 1);
		rght.add = root.add, rght.sum = root.add * (rght.r - rght.l + 1);
		root.add = -1;
	}
	return;
}
void build(int p, int l, int r)
{
	tr[p] = { l, r, -1, 0 };
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	//pushup(p);
	return;
}
void segadd(int p, int l, int r, int k)
{
	if((l <= tr[p].l) && (r >= tr[p].r))
	{
		tr[p].add = k;
		tr[p].sum = k * (tr[p].r - tr[p].l + 1);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid) segadd(p << 1, l, r, k);
	if(r > mid) segadd(p << 1 | 1, l, r, k);
	pushup(p);
	return;
}
ll install(int p)
{
	ll prev = tr[1].sum;
	int v = 1;
	while(top[p] != top[v])
	{
		if(dep[top[p]] < dep[top[v]]) swap(p, v);
		segadd(1, id[top[p]], id[p], 1);
		p = fa[top[p]];
	}
	if(dep[p] < dep[v]) swap(p, v);
	segadd(1, id[v], id[p], 1);
	return tr[1].sum - prev;
}
ll uninstall(int p)
{
	ll prev = tr[1].sum;
	segadd(1, id[p], id[p] + sz[p] - 1, 0);
	return prev - tr[1].sum;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 2; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		a++;
		add(a, i);
		add(i, a);
	}
	dfs1(1, 1, 1);
	dfs2(1, 1);
	build(1, 1, n);
	scanf("%d", &m);
	while(m--)
	{
		string s;
		int x;
		cin >> s;
		scanf("%d", &x);
		if(s[0] == 'i')
		{
			printf("%lld\n", install(x + 1));
		}
		else if(s[0] == 'u')
		{
			printf("%lld\n", uninstall(x + 1));
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
