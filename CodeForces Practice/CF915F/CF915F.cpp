#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 2000010;
int n;
int a[N];
struct Edge
{
	int u, v, w;
};
Edge e[N];
bool cmp1(const Edge &lhs, const Edge &rhs) { return lhs.w < rhs.w; }
bool cmp2(const Edge &lhs, const Edge &rhs) { return lhs.w > rhs.w; }
ll ans;
int fa[N], sz[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)fa[i] = i, sz[i] = 1;
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[i] = { u,v,max(a[u],a[v]) };
	}
	sort(e + 1, e + n, cmp1);
	for(int i = 1; i < n; i++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int fu = find(u), fv = find(v);
		ans += 1ll * w * sz[fu] * sz[fv];
		fa[fv] = fu, sz[fu] += sz[fv];
	}
	for(int i = 1; i <= n; i++)fa[i] = i, sz[i] = 1;
	for(int i = 1; i < n; i++)
		e[i].w = min(a[e[i].u], a[e[i].v]);
	sort(e + 1, e + n, cmp2);
	for(int i = 1; i < n; i++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int fu = find(u), fv = find(v);
		ans -= 1ll * w * sz[fu] * sz[fv];
		fa[fv] = fu, sz[fu] += sz[fv];
	}
	printf("%lld\n", ans);
	return 0;
}
