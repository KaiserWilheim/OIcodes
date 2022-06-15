#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
int f[N][2];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int fa)
{
	f[p][1] = 1;
	f[p][0] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		dfs(j, p);
		f[p][1] += f[j][0];
		f[p][0] += max(f[j][0], f[j][1]);
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
		scanf("%d%d", &u, &k);
		for(int j = 1; j <= k; j++)
		{
			int v;
			scanf("%d", &v);
			add(u + 1, v + 1);
			add(v + 1, u + 1);
		}
	}
	dfs(1, 0);
	printf("%d\n", n - max(f[1][1], f[1][0]));
	return 0;
}
