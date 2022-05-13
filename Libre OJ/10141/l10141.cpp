#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m, L, R;
int h[N], e[M], ne[M], idx;
int w[N], dep[N], sz[N];
int son[N], fa[N], top[N];
int id[N], nw[N], cnt;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

struct SegTree
{
	int l, r;
	int lc, rc;
	int sum, tag;
}tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	if(tr[p << 1].rc == tr[p << 1 | 1].lc)tr[p].sum--;
	tr[p].lc = tr[p << 1].lc;
	tr[p].rc = tr[p << 1 | 1].rc;
}
void pushdown(int p)
{
	if(tr[p].tag != 0)
	{
		auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
		left.lc = left.rc = left.tag = root.tag;
		rght.lc = rght.rc = rght.tag = root.tag;
		left.sum = rght.sum = 1;
		root.tag = 0;
	}
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].lc = tr[p].rc = nw[l];
		tr[p].sum = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void segadd(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].lc = tr[p].rc = k;
		tr[p].tag = k;
		tr[p].sum = 1;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		if(tr[p].l == l)L = tr[p].lc;
		if(tr[p].r == r)R = tr[p].rc;
		return tr[p].sum;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res;
	if(r <= mid)res = segsum(p << 1, l, r);
	else if(l > mid)res = segsum(p << 1 | 1, l, r);
	else 
	{
		res = segsum(p << 1, l, r) + segsum(p << 1 | 1, l, r);
		if(tr[p << 1].rc == tr[p << 1 | 1].lc)res--;
	}
	return res;
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
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = w[p], top[p] = t;
	if(!son[p]) return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
}
void addpath(int p, int q, int k)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]]) swap(p, q);
		segadd(1, id[top[p]], id[p], k);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q]) swap(p, q);
	segadd(1, id[q], id[p], k);
}
int sumpath(int p, int q)
{
	int res = 0, pre1 = 0, pre2 = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q), swap(pre1, pre2);
		res += segsum(1, id[top[p]], id[p]);
		if(R == pre1)res--;
		pre1 = L;
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q), swap(pre1, pre2);
	res += segsum(1, id[q], id[p]);
	if(R == pre1)res--;
	if(L == pre2)res--;
	return res;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	while(m--)
	{
		string op;
		int a, b, c;
		cin >> op;
		cin >> a >> b;
		if(op[0] == 'Q')
		{
			printf("%d\n", sumpath(a, b));
		}
		else if(op[0] == 'C')
		{
			cin >> c;
			addpath(a, b, c);
		}
	}
	return 0;
}
