#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = 10010;
int n, m, k;
struct Edge
{
	int a, b, w;
	bool operator < (const Edge &a)const
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
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		e[i] = { a,b,w };
	}
	if(m < n - k)
	{
		puts("No Answer");
		return 0;
	}
	sort(e + 1, e + 1 + m);
	int tot = n, ans = 0;
	for(int i = 1; i <= m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			ans += w;
			tot--;
		}
		if(tot == k)
		{
			cout << ans << endl;
			return 0;
		}
	}
	return 0;
}
