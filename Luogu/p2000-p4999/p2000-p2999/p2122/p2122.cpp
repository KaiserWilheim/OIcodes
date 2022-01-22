#include<bits/stdc++.h>
using namespace std;
const int N = 2010, M = N * N / 2;
int n, m, c;
struct Edge
{
	int a, b, w;
	bool operator < (const Edge &a) const
	{
		return w < a.w;
	}
}e[M];
struct Point
{
	int x, y;
	int operator * (const Point &a) const
	{
		return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y);
	}
}city[N];
int p[N];
int find(int x)
{
	if(p[x] != x)
	{
		p[x] = find(p[x]);
	}
	return p[x];
}
int main()
{
	cin >> n >> c;
	for(int i = 1; i <= n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		city[i] = { a,b };
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			if(city[i] * city[j] >= c)e[++m] = { i,j,city[i] * city[j] };
		}
	}
	int res = 0;
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			res += w;
		}
	}
	int flag = 0;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)flag++;
	}
	if(flag > 1)cout << -1 << endl;
	else cout << res << endl;
	return 0;
}
