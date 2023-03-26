#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
struct Edge
{
	int u, v, w;
	Edge(int _u, int _v, int _w) { u = _u, v = _v, w = _w; }
	bool operator < (const Edge &rhs)const
	{
		return w < rhs.w;
	}
};
int n, m;
int fa[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
void soyuz(int u, int v)
{
	int fu = find(u), fv = find(v);
	if(fu != fv)fa[fv] = fu;
}
int deg[N];
int bl[N];
int main()
{
	scanf("%d%d", &n, &m);
	int s; scanf("%d", &s);
	for(int i = 1; i <= n; i++)fa[i] = i;
	ll sum = 0;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		deg[u]++, deg[v]++;
		soyuz(u, v);
		sum += abs(u - v);
	}
	for(int i = 1; i <= n; i++)bl[i] = find(i);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)fa[j] = j;
		deg[s]++, deg[i]++;
		soyuz(s, i);
		ll ans = sum, pre = 0;
		for(int j = 1; j <= n; j++)
		{
			if(!(deg[j] & 1))continue;
			if(pre)
			{
				ans += j - pre;
				for(int k = pre; k < j; k++)soyuz(bl[k], bl[j]);
				pre = 0;
			}
			else pre = j;
		}
		vector<Edge>g;
		for(int j = 1; j <= n; j++)
		{
			if(deg[j])
			{
				if(pre && find(bl[j]) != find(bl[pre]))
					g.emplace_back(bl[j], bl[pre], abs(j - pre));
				pre = j;
			}
		}
		sort(g.begin(), g.end());
		for(int j = 0; j < g.size(); j++)
			if(find(g[j].u) != find(g[j].v))
				soyuz(g[j].u, g[j].v), ans += g[j].w * 2;
		printf("%lld ", ans);
		deg[s]--, deg[i]--;
	}
	putchar('\n');
	return 0;
}
