#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
	int v;
	int l, r;
}a[200010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++)
	{
		a[i] = { i, i - 1, i + 1 };
	}
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		if(a[x].r == n + 1)
		{
			int y = a[x].l;
			a[x].l = a[y].l;
			a[a[y].l].r = x;
			a[y].l = x;
			a[y].r = a[x].r;
			a[a[x].r].l = y;
			a[x].r = y;
		}
		else
		{
			int y = a[x].r;
			a[x].r = a[y].r;
			a[a[y].r].l = x;
			a[y].r = x;
			a[y].l = a[x].l;
			a[a[x].l].r = y;
			a[x].l = y;
		}
	}
	for(int i = a[0].r; i != n + 1; i = a[i].r)printf("%d ", a[i].v);
	putchar('\n');
	return 0;
}
