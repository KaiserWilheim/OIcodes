#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 998244353;
int n, m;
int a[N], d[N];
struct node
{
	int v, w, nxt;
}e[N << 1];
int head[N], tot;

inline int add(int x) { return x >= mod ? x - mod : x; }
inline int sub(int x) { return x < 0 ? x + mod : x; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }

inline void add(int a, int b, int c)
{
	e[++tot] = { b, c, head[a] };
	head[a] = tot;
}

int fa[N][20], dep[N];

inline void dfs(int x, int _f)
{
	fa[x][0] = _f, dep[x] = dep[_f] + 1;
	for (int i = 1; i <= 18; ++i) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = head[x], y; i; i = e[i].nxt)
		if ((y = e[i].v) != _f) dfs(y, x);
}

inline int get_fa(int x, int k)
{
	for (int i = 18; i >= 0; --i)
		if (k >= (1ll << i)) x = fa[x][i], k -= (1ll << i);
	return x;
}

int f[N], tmp1[N], tmp2[N], g[N], ans[N];

inline void get_f(int x)
{
	for (int i = head[x], y; i; i = e[i].nxt)
	{
		if ((y = e[i].v) == fa[x][0]) continue;
		get_f(y), f[x] = add(f[x] + f[y]);
	}
}

inline void get_g(int x)
{
	tmp1[x] = f[x], tmp2[x] = mul(f[x], f[x]);
	for (int i = head[x], y; i; i = e[i].nxt)
	{
		if ((y = e[i].v) == fa[x][0]) continue;
		get_g(y);
		tmp2[x] = add(tmp2[x] + mul(e[i].w, add(tmp2[y] + 1ll * 2 * tmp1[x] * tmp1[y] % mod)));
		tmp1[x] = add(tmp1[x] + mul(e[i].w, tmp1[y]));
	}
}

inline void getans(int x)
{
	for (int i = head[x], y; i; i = e[i].nxt)
	{
		if ((y = e[i].v) == fa[x][0]) continue;
		int E1 = sub(g[x] - mul(e[i].w, tmp1[y])), K = mul(mul(2, E1), tmp1[y]);
		g[y] = add(tmp1[y] + mul(e[i].w, E1));
		int E2 = sub(ans[x] - mul(e[i].w, add(tmp2[y] + K)));
		ans[y] = add(tmp2[y] + mul(e[i].w, add(E2 + K)));
		getans(y);
	}
}

signed main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i)scanf("%lld%lld", &a[i], &d[i]);
	for (int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dfs(1, 0), f[1] = a[1];
	for (int i = 2; i <= n; ++i)
	{
		int p = get_fa(i, d[i] + 1);
		f[i] += a[i], f[p] = sub(f[p] - a[i]);
	}
	get_f(1), get_g(1);
	g[1] = tmp1[1], ans[1] = tmp2[1];
	getans(1);
	scanf("%lld", &m);
	while (m--)
	{
		int x;
		scanf("%lld", &x);
		printf("%lld\n", ans[x]);
	}
	return 0;
}