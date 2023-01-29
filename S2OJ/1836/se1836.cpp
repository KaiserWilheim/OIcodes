#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n;
int now;
int h[N], e[M], ne[M], idx;
int a[N];
int pr[N];
int ans[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
	}
	int tmp = min(a[p], a[fa]);
	now += tmp * 2;
	a[p] -= tmp, a[fa] -= tmp;
	a[p] ? pr[fa] = p : 0;
}
void dfs2(int p, int fa)
{
	ans[p] = now;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		if(a[p])now++, a[p]--, dfs2(e[i], p), now--, a[p]++;
		else if(pr[e[i]])a[pr[e[i]]]--, now++, dfs2(e[i], p), a[pr[e[i]]]++, now--;
		else a[e[i]]++, now--, dfs2(e[i], p), a[pr[e[i]]]--, now++;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u++, v++;
		add(u, v), add(v, u);
		a[u]--, a[v]--;
		now += 2;
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}
