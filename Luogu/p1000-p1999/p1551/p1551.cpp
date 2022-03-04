#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int n, m, k;
int p[N];
int find(int x)
{
	if(x != p[x])
	{
		p[x] = find(p[x]);
	}
	return p[x];
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		int pa = find(a), pb = find(b);
		p[pa] = pb;
	}
	for(int i = 1; i <= k; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		int pa = find(a), pb = find(b);
		if(pa == pb)puts("Yes");
		else puts("No");
	}
	return 0;
}
