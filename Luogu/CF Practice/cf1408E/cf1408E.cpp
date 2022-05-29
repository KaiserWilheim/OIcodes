#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010;
int n, m;
int a[N], b[N];
int fa[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
struct Edge
{
	int v, x, y;
	bool operator <(const Edge &a)const
	{
		return v > a.v;
	}
}e[N];
int tot;
ll res;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= 200000; i++)
		fa[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j++)
		{
			int p;
			scanf("%d", &p);
			e[++tot] = { a[i] + b[p],i + n,p };
			res += a[i] + b[p];
		}
	}
	sort(e + 1, e + tot + 1);
	for(int i = 1; i <= tot; i++)
	{
		int pa = find(e[i].x), pb = find(e[i].y);
		if(pa != pb)
		{
			fa[pa] = pb;
			res -= e[i].v;
		}
	}
	printf("%lld\n", res);
	return 0; 
}
