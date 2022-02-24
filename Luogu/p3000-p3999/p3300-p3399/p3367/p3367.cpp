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
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int op, a, b;
		scanf("%d%d%d", &op, &a, &b);
		int pa = find(a), pb = find(b);
		if(op == 1)
		{
			p[pa] = pb;
		}
		else if(op == 2)
		{
			if(pa == pb)puts("Y");
			else puts("N");
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
