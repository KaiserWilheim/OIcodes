#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m, q;
int crow[N], trow[N];
int ccol[N], tcol[N];
void solve()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
		ccol[i] = tcol[i] = 0;
	for(int i = 1; i <= m; i++)
		crow[i] = trow[i] = 0;
	for(int i = 1; i <= q; i++)
	{
		int op, x, c;
		scanf("%d%d%d", &op, &x, &c);
		if(op == 0)ccol[x] = c, tcol[x] = i;
		else if(op == 1)crow[x] = c, trow[x] = i;
		else puts("Youwike AK NOI!");
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(tcol[i] >= trow[j])printf("%d ", ccol[i]);
			else printf("%d ", crow[j]);
		}
		putchar('\n');
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
