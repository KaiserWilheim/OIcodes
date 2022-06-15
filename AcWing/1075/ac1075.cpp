#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
int sum[N];
bool vis[N];
int ans;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int p, int fa)
{
	int d1 = 0, d2 = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		int d = dfs(j, p) + 1;
		if(d >= d1)d2 = d1, d1 = d;
		else if(d > d2)d2 = d;
	}
	ans = max(ans, d1 + d2);
	return d1;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 2; j * i <= n; j++)
			sum[i * j] += i;
	for(int i = 2; i <= n; i++)
		if(i > sum[i])
		{
			add(sum[i], i);
			add(i, sum[i]);
			vis[i] = true;
		}
	for(int i = 1; i <= n; i++)
		if(!vis[i])dfs(i, 0);
	printf("%d\n", ans);
	return 0;
}
