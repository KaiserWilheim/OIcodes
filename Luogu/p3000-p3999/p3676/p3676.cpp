#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
typedef int arr[N];
typedef long long ll;
arr h, e, ne;
int n, m, idx, cnt;
arr w, c, fa, sz, id, pos, dep, son, top;
ll ans, c1[N], c2[N];
void dfs1(int u)
{
	dep[u] = dep[fa[u]] + (sz[u] = 1);
	for(int i = h[u], v = e[i]; i; v = e[i = ne[i]])
		if(v ^ fa[u])
		{
			fa[v] = u, dfs1(v), w[u] += w[v], sz[u] += sz[v];
			if(sz[v] > sz[son[u]])son[u] = v;
		}ans += 1ll * w[u] * w[u];
}
inline void Mdy(int x, ll w)
{
	for(int i = x; i <= n; i += i & (-i))
		c1[i] += w, c2[i] += ( ll )x * w;
}
inline ll Qry(int x)
{
	ll w = 0;
	for(int i = x; i; i -= i & (-i))
		w += 1ll * (x + 1) * c1[i] - c2[i];
	return w;
}
void dfs2(int u, int t)
{
	top[u] = t; pos[id[u] = ++cnt] = u;
	Mdy(id[u], w[u] - w[pos[cnt - 1]]);
	if(son[u])
		dfs2(son[u], t);
	for(int i = h[u], v = e[i]; i; v = e[i = ne[i]])
		if(v ^ fa[u] && v ^ son[u])
			dfs2(v, v);
}
inline ll qry(int u)
{
	int k = 0, x = Qry(1); ll s = 0;
	for(; u; u = fa[top[u]])
		k += id[u] - id[top[u]] + 1,
		s += Qry(id[u]) - Qry(id[top[u]] - 1);
	return ans + x * ((k + 1) * x - (s << 1));
}
inline void mdy(int u, int x)
{
	int k = 0; ll s = 0;
	for(; u; u = fa[top[u]])
		k += id[u] - id[top[u]] + 1,
		s += Qry(id[u]) - Qry(id[top[u]] - 1),
		Mdy(id[top[u]], x), Mdy(id[u] + 1, -x);
	ans += x * (x * k + (s << 1));
}
inline void add(int u, int v)
{
	e[++idx] = v, ne[idx] = h[u], h[u] = idx;
}
int main()
{
	scanf("%d%d", &n, &m);
	int u, v, o;
	for(int i = 2; i <= n; i++)
		scanf("%d%d", &u, &v), add(u, v), add(v, u);
	for(int i = 1; i <= n; i++)
		scanf("%d", c + i), w[i] = c[i];
	dfs1(1); dfs2(1, 1);
	while(m--)
	{
		scanf("%d%d", &o, &u);
		if(o == 1)
		{
			scanf("%d", &v);
			v -= c[u], c[u] += v;
			mdy(u, v);
		}
		else
		{
			printf("%lld\n", qry(u));
		}
	}
	return 0;
}
