#include<bits/stdc++.h>
using namespace std;
const int N = 5010, M = 200010;
struct Edge
{
	int a, b, w;
	bool operator < (const Edge &a) const
	{
		return w < a.w;
	}
}e[M];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		e[i] = { a,b,w };
	}
	sort(e + 1, e + 1 + m);
	long long ans = 0;
	for(int i = 1; i <= m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			ans += w;
		}
	}
	int flag = 0;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)flag++;
	}
	if(flag > 1)cout << "orz" << endl;
	else cout << ans << endl;
	return 0;
}
