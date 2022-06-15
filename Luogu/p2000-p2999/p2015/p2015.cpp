#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = N << 1;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int f[N][N];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		for(int j = m; j > 0; j--)
			for(int k = 0; k + 1 <= j; k++)
				f[p][j] = max(f[p][j], f[p][j - k - 1] + f[e[i]][k] + w[i]);
	}
	return;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	dfs(1, 0);
	printf("%d\n", f[1][m]);
	return 0;
}
