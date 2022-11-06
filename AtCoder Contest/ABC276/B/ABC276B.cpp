#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
set<int>e[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].insert(v);
		e[v].insert(u);
	}
	for(int i = 1; i <= n; i++)
	{
		printf("%d", e[i].size());
		for(auto k : e[i])
			printf(" %d", k);
		putchar('\n');
	}
	return 0;
}
