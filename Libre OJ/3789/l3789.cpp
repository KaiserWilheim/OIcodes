using namespace std;
#define ll long long
const int N = 250010, M = N << 1;
int n, m;
struct Edge
{
	int h[N], e[M], ne[M], idx;
	ll w[M];
	void init()
	{
		memset(h, -1, sizeof(h));
		idx = 0;
	}
	void add(int a, int b, ll c)
	{
		e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
	}
}t, v;
struct Segtree
{
	int l, r;
	ll v;
}tr[N << 3];
int dep[N], sz[N], top[N], fa[N], son[N], id[N], cnt;
ll nw[N], rk[N];
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	for(int i = t.h[p]; ~i; i = t.ne[i])
	{
		int j = t.e[i];
		if(j == father) continue;
		rk[j] = t.w[i];
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j]) son[p] = j;
	}
}
void dfs2(int p, int tp)
{
	id[p] = ++cnt, nw[cnt] = rk[p], top[p] = tp;
	if(!son[p]) return;
	dfs2(son[p], tp);
	for(int i = t.h[p]; ~i; i = t.ne[i])
	{
		int j = t.e[i];
		if(j == fa[p] || j == son[p]) continue;
		dfs2(j, j);
	}
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].v = nw[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	tr[p].v = min(tr[p << 1].v, tr[p << 1 | 1].v);
}
ll segmin(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].v;
	ll res = 0x3f3f3f3f3f3f3f3f;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = min(res, segmin(p << 1, l, r));
	if(r > mid)res = min(res, segmin(p << 1 | 1, l, r));
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
ll minpath(int p, int q)
{
	ll res = 0x3f3f3f3f3f3f3f3f;
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		res = min(res, segmin(1, id[top[p]], id[p]));
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	res = min(res, segmin(1, id[q] + 1, id[p]));
	return res;
}
bool cmp(const int a, const int b)
{
	return id[a] < id[b];
}
int k, a[N];
bool imp[N];
int sta[N], tt;
void build()
{
	v.idx = 0;
	sort(a + 1, a + 1 + k, cmp);
	sta[tt = 1] = 1;
	v.h[1] = -1;
	for(int i = 1; i <= k; i++)
	{
		int g = lca(a[i], sta[tt]);
		if(g != sta[tt])
		{
			while(id[g] < id[sta[tt - 1]])
			{
				int p = sta[tt - 1], q = sta[tt--];
				ll d = minpath(p, q);
				v.add(p, q, d);
				v.add(q, p, d);
			}
			if(id[g] > id[sta[tt - 1]])
			{
				ll d = minpath(g, sta[tt]);
				v.h[g] = -1;
				v.add(g, sta[tt], d);
				v.add(sta[tt], g, d);
				tt--;
				sta[++tt] = g;
			}
			else
			{
				int p = sta[tt - 1], q = sta[tt--];
				ll d = minpath(p, q);
				v.add(p, q, d);
				v.add(q, p, d);
			}
		}
		v.h[a[i]] = -1;
		sta[++tt] = a[i];
	}
	while(tt > 1)
	{
		int p = sta[tt - 1], q = sta[tt--];
		ll d = minpath(p, q);
		v.add(p, q, d);
		v.add(q, p, d);
	}
}
ll dp(int p, int fa)
{
	ll res = 0;
	for(int i = v.h[p]; ~i; i = v.ne[i])
	{
		int j = v.e[i];
		ll w = v.w[i];
		if(j == fa)continue;
		if(imp[j])res += w;
		else res += min(dp(j, p), w);
	}
	return res;
}
int main()
{
	t.init();
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		ll c;
		scanf("%d%d%lld", &a, &b, &c);
		t.add(a, b, c);
		t.add(b, a, c);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	scanf("%d", &m);
	while(m--)
	{
		memset(imp, false, sizeof(imp));
		scanf("%d", &k);
		for(int i = 1; i <= k; i++)
		{
			scanf("%d", &a[i]);
			imp[a[i]] = true;
		}
		build();
		printf("%lld\n", dp(1, 0));
	}
	return 0;
}
