#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = 100010;
int n, m;
struct Edge
{
	int a, b;
}e[M];
int p[N];
int find(int x)
{
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(e, 0, sizeof(e));
		for(int i = 1; i <= n; i++) p[i] = i;
		for(int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			e[i] = { a, b };
		}
		int res = 0;
		int maxn = -1;
		for(int i = 0; i < m; i++)
		{
			int a = find(e[i].a), b = find(e[i].b);
			if(a != b)p[a] = b;
		}
		for(int i = 1; i <= n; i++)
		{
			if(find(i) == i)res++;
		}
		cout << res - 1 << endl;
	}
	return 0;
}
