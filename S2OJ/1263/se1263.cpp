#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct SegTree
{
	int l, r;
	ll sum;
}tr[N << 3];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int p, int vater, int depth)
{
	dep[p] = depth, fa[p] = vater, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == vater)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	id[p] = ++cnt, nw[cnt] = w[p], top[p] = t;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p])continue;
		dfs2(j, j);
	}
}
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = nw[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}
void segchg(int p, int ed, ll k)
{
	if((tr[p].l == ed) && (tr[p].r == ed))
	{
		tr[p].sum = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(ed <= mid)segchg(p << 1, ed, k);
	if(ed > mid)segchg(p << 1 | 1, ed, k);
	pushup(p);
	return;
}
ll segsum(int p, int l, int r)
{
	if((tr[p].l >= l) && (tr[p].r <= r))return tr[p].sum;
	ll res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
ll sumtree(int p)
{
	return segsum(1, id[p], id[p] + sz[p] - 1);
}
ll sumpath(int p, int q)
{
	ll res = 0;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		res += segsum(1, id[top[p]], id[p]);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	res += segsum(1, id[q], id[p]);
	return res;
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
int get_v(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		if(fa[top[p]] == q)return top[p];
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return son[q];
}
using namespace std;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	for(int i = 1; i <= n; i++)scanf("%d", &w[i]);
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	int rt = 1;
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		scanf("%d%d", &op, &x);
		if(op == 1)
		{
			rt = x;
		}
		else if(op == 2)
		{
			ll z;
			scanf("%lld", &z);
			segchg(1, id[x], z);
		}
		else if(op == 3)
		{
			if(x == rt)
			{
				printf("%lld\n", tr[1].sum);
			}
			else
			{
				if(lca(x, rt) != x)
				{
					printf("%lld\n", sumtree(x));
				}
				else
				{
					printf("%lld\n", tr[1].sum - sumtree(get_v(rt, x)));
				}
			}
		}
		else if(op == 4)
		{
			scanf("%d", &y);
			printf("%lld\n", sumpath(x, y));
		}
	}
	return 0;
}

