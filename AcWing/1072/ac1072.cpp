#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1;
int n;
int h[N], e[M], ne[M], w[M], idx;
int ans;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int p, int fa)
{
	int dis = 0;
	int d1 = 0, d2 = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		int d = dfs(j, p) + w[i];
		dis = max(dis, d);
		if(d >= d1)d2 = d1, d1 = d;
		else if(d > d2)d2 = d;
	}
	ans = max(ans, d1 + d2);
	return dis;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c), add(b, a, c);
	}
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
