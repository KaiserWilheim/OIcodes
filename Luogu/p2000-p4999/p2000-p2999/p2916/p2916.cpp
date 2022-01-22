#include<bits/stdc++.h>
using namespace std;
const int N = 10010, M = 100010;
int n, m;
struct Edge
{
	int a, b, w;
	bool operator< (const Edge &t)const
	{
		return w < t.w;
	}
}e[M];
int p[N];
int find(int x)
{
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}
int reich[N];
int main()
{
	scanf("%d%d", &n, &m);
	{
		int minn = 0x3f3f3f3f;
		memset(e, 0, sizeof(e));
		for(int i = 1; i <= n; i++) p[i] = i;
		for(int i = 1; i <= n; i++)scanf("%d", &reich[i]), minn = min(minn, reich[i]);
		for(int i = 0; i < m; i++)
		{
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			e[i] = { a, b, w * 2 + reich[a] + reich[b] };
		}
		sort(e, e + m);
		int res = 0;
		for(int i = 0; i < m; i++)
		{
			int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
			if(a != b)p[a] = b, res += e[i].w;
		}
		cout << res + minn << endl;
	}
	return 0;
}
