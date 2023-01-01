#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll a[N], c[N], d[N];
bool vis[N];
int sz[N], msiz[N], tot;
int rt;
void getrt(int p, int fa)
{
	sz[p] = 1, msiz[p] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa || vis[v])continue;
		getrt(v, p);
		sz[p] += sz[v];
		msiz[p] = max(msiz[p], sz[v]);
	}
	msiz[p] = max(msiz[p], tot - sz[p]);
	if(!rt || msiz[p] < msiz[rt])rt = p;
}
ll s1[N], s2[N], q1[N], q2[N];
int hh1, hh2, tt1, tt2;
ll ans;
void dfs(int p, int fa, ll maxn, ll minn)
{
	if(c[p] - d[p] >= maxn)
		s1[++tt1] = c[p] - d[p];
	s2[++tt2] = minn;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa || vis[v])continue;
		d[v] = d[p] + w[i], c[v] = c[p] + a[v];
		dfs(v, p, max(maxn, c[p] - d[p]), min(minn, c[p] - d[v]));
	}
}
void calc(int p)
{
	int l;
	hh1 = hh2 = 0;
	d[p] = 0, c[p] = a[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(vis[v])continue;
		tt1 = tt2 = 0;
		d[v] = w[i], c[v] = c[p] + a[v];
		dfs(v, p, c[p] - d[p], c[p] - d[v]);
		sort(s1 + 1, s1 + 1 + tt1);
		sort(s2 + 1, s2 + 1 + tt2);
		l = 1;
		for(int i = tt2; i; i--)
		{
			while(l <= tt1 && s1[l] + s2[i] - a[p] < 0)l++;
			ans -= tt1 - l + 1;
		}
		for(int i = 1; i <= tt1; i++)q1[++hh1] = s1[i];
		for(int i = 1; i <= tt2; i++)q2[++hh2] = s2[i];
	}
	sort(q1 + 1, q1 + 1 + hh1);
	sort(q2 + 1, q2 + 1 + hh2);
	l = 1;
	for(int i = hh2; i; i--)
	{
		if(q2[i] >= 0)ans++;
		while(l <= hh1 && q1[l] + q2[i] - a[p] < 0)l++;
		ans += hh1 - l + 1;
	}
	ans += hh1;
}
void solve(int p)
{
	vis[p] = true;
	calc(p);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(vis[v])continue;
		rt = 0, tot = sz[v];
		getrt(v, p);
		solve(rt);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	rt = 0, tot = n;
	getrt(1, 0);
	solve(rt);
	printf("%lld\n", ans);
	return 0;
}
