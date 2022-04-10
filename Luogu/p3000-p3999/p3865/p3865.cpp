#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int a[N], st[N][30];

void build(int n)
{
	for(int i = 1; i <= n; i++) st[i][0] = a[i];
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(n);
	while(m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int k = log2(r - l + 1);
		printf("%d\n", max(st[l][k], st[r - (1 << k) + 1][k]));
	}
	return 0;
}
