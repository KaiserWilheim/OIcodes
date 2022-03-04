#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
int n, m;
struct Point
{
	long long x, y;
	long long operator * (const Point &b) const
	{
		return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	}
}city[N];
bool vis[N];
long long d[N];
void prim()
{
	memset(d, 0x3f, sizeof(d));
	memset(vis, false, sizeof(vis));
	d[1] = 0;
	for(int i = 1; i < n; i++)
	{
		int x = -1;
		for(int j = 1; j <= n; j++)
		{
			if((!vis[j]) && ((x == -1) || d[j] < d[x]))x = j;
		}
		vis[x] = true;
		for(int j = 1; j <= n; j++)
		{
			if(!vis[j])d[j] = min(d[j], city[x] * city[j]);
		}
	}
}
int main()
{
	scanf("%d", &n);
	{
		for(int i = 1; i <= n; i++)scanf("%lld%lld", &city[i].x, &city[i].y);
		prim();
		double res = 0;
		for(int i = 1; i <= n; i++)res += sqrt(( double )d[i]);
		printf("%.2lf\n", res);
	}
	return 0;
}
