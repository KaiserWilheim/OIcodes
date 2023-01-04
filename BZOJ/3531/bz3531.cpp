#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int m, n;
int w[N], c[N], h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N], sz[N], top[N], fa[N], son[N];
int id[N], nw[N], cnt;
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
	id[p] = ++cnt, nw[cnt] = p, top[p] = t;
	if(!son[p]) return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
}
struct SegTree
{
	int l, r;
	int ls, rs;
	int sum, max;
}tr[N << 5];
int tot;
int rt[N];
void pushup(int p)
{
	tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum;
	tr[p].max = max(tr[tr[p].ls].max, tr[tr[p].rs].max);
}
void segchg(int p,int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].sum = tr[p].max = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)
	{
		if(!tr[p].ls)
		{
			tr[p].ls = ++tot;
			tr[tr[p].ls].l = tr[p].l;
			tr[tr[p].ls].r = mid;
		}
		segchg(tr[p].ls, l, r, k);
	}
	if(r > mid)
	{
		if(!tr[p].rs)
		{
			tr[p].rs = ++tot;
			tr[tr[p].rs].l = mid + 1;
			tr[tr[p].rs].r = tr[p].r;
		}
		segchg(tr[p].rs, l, r, k);
	}
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(!p)return 0;
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	int res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res += segsum(tr[p].ls, l, r);
	if(r > mid)res += segsum(tr[p].rs, l, r);
	return res;
}
int segmax(int p, int l, int r)
{
	if(!p)return 0;
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].max;
	int res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = max(res, segmax(tr[p].ls, l, r));
	if(r > mid)res = max(res, segmax(tr[p].rs, l, r));
	return res;
}
int sumpath(int p, int q)
{
	int rc = c[p];
	int res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		res += segsum(rt[rc], id[top[p]], id[p]);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	res += segsum(rt[rc], id[q], id[p]);
	return res;
}
int maxpath(int p, int q)
{
	int rc = c[p];
	int res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		res = max(res, segmax(rt[rc], id[top[p]], id[p]));
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	res = max(res, segmax(rt[rc], id[q], id[p]));
	return res;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &w[i], &c[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for(int i = 1; i <= n; i++)
	{
		if(!rt[c[i]])
		{
			rt[c[i]] = ++tot;
			tr[tot].l = 1;
			tr[tot].r = n;
		}
		segchg(rt[c[i]], id[i], id[i], w[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		string op;
		int x, y;
		cin >> op >> x >> y;
		if(op[1] == 'C')
		{
			segchg(rt[c[x]], id[x], id[x], 0);
			c[x] = y;
			segchg(rt[c[x]], id[x], id[x], w[x]);
		}
		else if(op[1] == 'W')
		{
			segchg(rt[c[x]], id[x], id[x], y);
			w[x] = y;
		}
		else if(op[1] == 'S')
		{
			printf("%d\n", sumpath(x, y));
		}
		else if(op[1] == 'M')
		{
			printf("%d\n", maxpath(x, y));
		}
		else
		{
			puts("Sieg Heil!");
		}
	}
	return 0;
}
