#include <bits/stdc++.h>
using namespace std;
const int N = 2010, M = 4000010;
#define int long long
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
struct edge
{
	int a, b, w;
	bool operator < (const edge &a) const
	{
		return w < a.w;
	}
}e[M];
signed main()
{
	int n, m = 0;
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++)
		{
			int x;
			scanf("%lld", &x);
			e[m++] = { i - 1,j,x };
		}
	}
	for(int i = 1; i <= n; i++)p[i] = i;
	sort(e, e + m);
	int ans = 0;
	for(int i = 0; i < m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			ans += w;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
