#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, k[N], ans;
int f[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		dfs(j, p);
		k[p] = max(k[p], k[j] - 1);
		f[p] = max(f[p], f[j] - 1);
	}
	if(!f[p])
	{
		ans++;
		f[p] = k[p];
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 2; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(i, x), add(x, i);
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &k[i]);
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
