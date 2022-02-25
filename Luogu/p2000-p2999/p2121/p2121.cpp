#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m, k;
struct edge
{
	int a, b, w;
	bool operator < (const edge &a) const
	{
		return w > a.w;
	}
}e[N];
int p[N];
int find(int x)
{
	if(x != p[x])p[x] = find(p[x]);
	return p[x];
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		e[i] = { a,b,w };
	}
	sort(e + 1, e + m + 1);
	int tot = 0;
	for(int i = 1, j = 0; i <= m && j < k; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			tot += w;
			j++;
		}
	}
	printf("%d", tot);
	return 0;
}
