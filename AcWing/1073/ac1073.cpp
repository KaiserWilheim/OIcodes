#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1;
const int INF = 0x3f3f3f3f;
int n;
int h[N], e[M], ne[M], w[M], idx;
int d1[N], d2[N], up[N], p1[N];
bool leaf[N];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int p, int fa)
{
	d1[p] = d2[p] = -INF;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		int d = dfs(j, p) + w[i];
		if(d >= d1[p])d2[p] = d1[p], d1[p] = d, p1[p] = j;
		else if(d > d2[p])d2[p] = d;
	}
	if(d1[p] == -INF)
	{
		d1[p] = d2[p] = 0;
		leaf[p] = true;
	}
	return d1[p];
}
void find(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		if(p1[p] == j)up[j] = max(up[p], d2[p]) + w[i];
		else up[j] = max(up[p], d1[p]) + w[i];
		find(j, p);
	}
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
	find(1, 0);
	int ans = d1[1];
	for(int i = 2; i <= n; i++)
		if(leaf[i])ans = min(ans, up[i]);
		else ans = min(ans, max(d1[i], up[i]));
	printf("%d\n", ans);
	return 0;
}
