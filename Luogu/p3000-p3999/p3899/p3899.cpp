#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int n, m;
struct SegTree
{
	int s[2];
	ll sum;
};
SegTree tr[N * 40];
int rt[N], cnt;
void pushup(int p)
{
	tr[p].sum = tr[tr[p].s[0]].sum + tr[tr[p].s[1]].sum;
}
int build(int l, int r)
{
	int p = ++cnt;
	if(l == r)
	{
		return p;
	}
	int mid = (l + r) >> 1;
	tr[p].s[0] = build(l, mid);
	tr[p].s[1] = build(mid + 1, r);
	return p;
}
int segadd(int q, int l, int r, int pos, ll k)
{
	int p = ++cnt;
	if(l == r)
	{
		tr[p].sum = tr[q].sum + k;
		return p;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)
	{
		tr[p].s[1] = tr[q].s[1];
		tr[p].s[0] = segadd(tr[q].s[0], l, mid, pos, k);
	}
	else
	{
		tr[p].s[0] = tr[q].s[0];
		tr[p].s[1] = segadd(tr[q].s[1], mid + 1, r, pos, k);
	}
	pushup(p);
	return p;
}
ll segsum(int p, int q, int l, int r, int dl, int dr)
{
	if(l >= dl && r <= dr)return tr[p].sum - tr[q].sum;
	ll res = 0;
	int mid = (l + r) >> 1;
	if(dl <= mid)res += segsum(tr[p].s[0], tr[q].s[0], l, mid, dl, dr);
	if(dr > mid)res += segsum(tr[p].s[1], tr[q].s[1], mid + 1, r, dl, dr);
	return res;
}
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N], sz[N], dfn[N], tot;
void dfs1(int p, int fa)
{
	dep[p] = dep[fa] + 1, sz[p] = 1, dfn[p] = ++tot;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
	}
}
void dfs2(int p, int fa)
{
	rt[dfn[p]] = segadd(rt[dfn[p] - 1], 1, n, dep[p], sz[p] - 1);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs2(e[i], p);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	rt[0] = build(1, n);
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= m; i++)
	{
		int p, k;
		scanf("%d%d", &p, &k);
		ll ans = segsum(rt[dfn[p] + sz[p] - 1], rt[dfn[p] - 1], 1, n, dep[p] + 1, dep[p] + k);
		ans += 1ll * min(k, dep[p] - 1) * (sz[p] - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
