#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, ans, fa[N * 3];
int find(int u)
{
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n * 3; i++) { fa[i] = i; }
	for(; m; m--)
	{
		int opt, u, v;
		scanf("%d%d%d", &opt, &u, &v);
		if((u > n) || (v > n)) { ans++; continue; }
		if(opt == 1)
		{
			if((find(u + n) == find(v)) || (find(u) == find(v + n))) { ans++; }
			else
			{
				fa[find(u)] = find(v);
				fa[find(u + n)] = find(v + n);
				fa[find(u + n + n)] = find(v + n + n);
			}
		}
		else
		{
			if((find(u) == find(v)) || (find(u) == find(v + n))) { ans++; }
			else
			{
				fa[find(u + n)] = find(v);
				fa[find(u + n + n)] = find(v + n);
				fa[find(u)] = find(v + n + n);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
