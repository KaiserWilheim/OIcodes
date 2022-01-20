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
int idx = 0;
int main()
{
	scanf("%d%d", &m, &n);
	{
		memset(e, 0, sizeof(e));
		for(int i = 1; i <= n; i++) p[i] = i;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				int w;
				scanf("%d", &w);
				if((j < i) && (w != 0) && (w < m))e[++idx] = { i, j, w };
			}
			e[++idx] = { 0,i,m };
		}
		sort(e, e + idx);
		int res = 0;
		for(int i = 1; i <= idx; i++)
		{
			int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
			if(a != b)p[a] = b, res += e[i].w;
		}
		cout << res << endl;
	}
	return 0;
}
