#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 400010;
int n, m, q;
int a[N];
int main()
{
	scanf("%d%d", &n, &m);
	scanf("%d", &q);
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = x;
	}
	for(int i = 1; i <= q; i++)
	{
		int l;
		scanf("%d", &l);
		if(a[l + 1] != a[l] + 1 && a[l] != n)a[l]++;
	}
	for(int i = 1; i <= m; i++)
		printf("%d ", a[i]);
	putchar('\n');
	return 0;
}
