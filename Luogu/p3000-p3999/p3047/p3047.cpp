#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int k;
int h[N], e[M], ne[M], idx;
int w[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int f[N][30];
void dfs1(int p, int fa)
{
	f[p][0] = w[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		for(int j = 0; j < k; j++)
			f[p][j + 1] += f[e[i]][j];
	}
}
void dfs2(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		for(int j = k; j >= 2; j--)
			f[e[i]][j] -= f[e[i]][j - 2];
		for(int j = 0; j < k; j++)
			f[e[i]][j + 1] += f[p][j];
		dfs2(e[i], p);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
	{
		int sum = 0;
		for(int j = 0; j <= k; j++)sum += f[i][j];
		printf("%d\n", sum);
	}
	return 0;
}