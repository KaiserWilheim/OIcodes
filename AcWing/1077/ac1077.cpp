#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
int w[N];
int f[N][3];
bool st[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p)
{
	f[p][2] = w[p];
	int sum = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		dfs(j);
		f[p][0] += min(f[j][1], f[j][2]);
		f[p][2] += min(min(f[j][0], f[j][1]), f[j][2]);
		sum += min(f[j][1], f[j][2]);
	}
	f[p][1] = 1e9;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		f[p][1] = min(f[p][1], sum - min(f[j][1], f[j][2]) + f[j][2]);
	}
	return;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int u, k;
		scanf("%d", &u);
		scanf("%d%d", &w[u], &k);
		for(int j = 1; j <= k; j++)
		{
			int v;
			scanf("%d", &v);
			add(u, v);
			st[v] = true;
		}
	}
	int rt = 1;
	while(st[rt])rt++;
	dfs(rt);
	printf("%d\n", min(f[rt][1], f[rt][2]));
	return 0;
}
