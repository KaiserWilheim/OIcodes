#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010, M = N << 1;
int n, m, q;
int a[N];
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &rhs)const { return w < rhs.w; }
}edge[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
struct DSU
{
	int p[N], rt[N];
	void init(int n) { for(int i = 1; i <= n; i++)p[i] = i, rt[i] = i; }
	int find(int x)
	{
		if(p[x] != x)p[x] = find(p[x]);
		return p[x];
	}
}dsu;
int b[N];
int fa[N][20], val[N][20];
int sum[N];
void dfs(int p, int fa)
{
	sum[p] = a[p];
	::fa[p][0] = fa;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		sum[p] += sum[e[i]];
	}
	val[p][0] = sum[p] - b[fa];
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld%lld%lld", &n, &m, &q);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%lld%lld%lld", &edge[i].u, &edge[i].v, &edge[i].w);
	sort(edge + 1, edge + 1 + m);
	dsu.init(n + n);
	int cnt = n + 1;
	for(int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v;
		int fu = dsu.find(u), fv = dsu.find(v);
		if(fu != fv)
		{
			add(dsu.rt[fu], cnt), add(cnt, dsu.rt[fu]);
			add(dsu.rt[fv], cnt), add(cnt, dsu.rt[fv]);
			b[cnt] = edge[i].w;
			dsu.p[fv] = fu;
			dsu.rt[fu] = cnt;
			cnt++;
		}
		if(cnt == n + n)break;
	}
	dfs(n + n - 1, 0);
	val[n + n - 1][0] = -1e15;
	for(int k = 1; k <= 18; k++)
		for(int i = 1; i <= n + n - 1; i++)
			fa[i][k] = fa[fa[i][k - 1]][k - 1], val[i][k] = min(val[i][k - 1], val[fa[i][k - 1]][k - 1]);
	while(q--)
	{
		int p, v;
		scanf("%lld%lld", &p, &v);
		if(b[fa[p][0]] > v + a[p])
		{
			printf("%lld\n", v + a[p]);
			continue;
		}
		for(int k = 17; k >= 0; k--)
			if(v + val[p][k] >= 0)p = fa[p][k];
		int res = v + sum[p];
		printf("%lld\n", res);
	}
	return 0;
}
