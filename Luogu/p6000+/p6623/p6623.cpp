#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 550010, M = N << 1, K = 21;
int n, m;
int a[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll w[K][M];
ll ans;
ll dfs(int p, int fa, int dep)
{
	ll tmp = a[p];
	for(int k = 0; k <= 20; k++)w[k][(dep + a[p]) & ((1 << k) - 1)] ^= 1 << k;
	for(int k = 0; k <= 20; k++)tmp ^= w[k][dep & ((1 << k) - 1)];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		tmp ^= dfs(e[i], p, dep + 1);
	}
	for(int k = 0; k <= 20; k++)tmp ^= w[k][dep & ((1 << k) - 1)];
	ans += tmp;
	return tmp;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 2; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(x, i), add(i, x);
	}
	dfs(1, 0, 0);
	printf("%lld\n", ans);
	return 0;
}
