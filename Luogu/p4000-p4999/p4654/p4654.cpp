#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 2000010;
int n, rt, m;
int h[N], e[M], ne[M], idx;
int sz[N], fa[N], f[N];
bool vis[N];
int sum[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int father)
{
	fa[p] = father, sz[p] = 0;
	int h1 = 0, h2 = 0;
	for (int i = h[p]; ~i; i = ne[i])
		if (e[i] != father)sz[p]++;
	if (p != rt)
		sum[p] = sum[father] + sz[p] - (p != m);
	for (int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if (j == fa[p])continue;
		dfs(j, p);
		if (f[j] > h1)h2 = h1, h1 = f[j];
		else if (f[j] > h2)h2 = f[j];
	}
	f[p] = h2 + sz[p];
}
bool chq(int k)
{
	for (int i = m, cnt = 1; i != rt; i = fa[i], cnt++)
	{
		int tmp = 0;
		for (int j = h[i]; ~j; j = ne[j])
		{
			int v = e[j];
			if (vis[v] || sum[i] + f[v] <= k)continue;
			if (!cnt)return false;
			tmp++;
			cnt--;
		}
		k -= tmp;
	}
	return k >= 0;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &rt, &m);
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dfs(rt, 0);
	f[rt] = 0;
	for (int i = m; i; i = fa[i])vis[i] = true;
	int l = 0, r = 1e8;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (chq(mid))r = mid;
		else l = mid + 1;
	}
	printf("%d\n", r);
	return 0;
}