#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = 1000010;
int n, m, k;
struct Edge
{
	int a, b;
	long long w;
	bool operator < (const Edge &a)const
	{
		return w < a.w;
	}
}e[M];
struct Node
{
	long long x, y;
}city[N];
long long dis(Node a, Node b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= n; i++)
	{
		long long a, b;
		scanf("%lld%lld", &a, &b);
		city[i] = { a,b };
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
		{
			e[++m] = { i,j,dis(city[i],city[j]) };
		}
	}
	sort(e + 1, e + 1 + m);
	int tot = n;
	for(int i = 1; i <= m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			tot--;
		}
		if(tot < k)
		{
			double ans = sqrt(w);
			printf("%.2lf\n", ans);
			return 0;
		}
	}
	return 0;
}
