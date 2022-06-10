#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010;
int n;
int a[N], f[N], g[N];
int main()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		f[i] = g[i] = 1;
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < i; j++)
			if(a[i] > a[j])f[i] = max(f[i], f[j] + 1);
	for(int i = n; i >= 1; i--)
		for(int j = n; j > i; j--)
			if(a[i] > a[j])g[i] = max(g[i], g[j] + 1);
	for(int i = 1; i <= n; i++)
		maxn = max(maxn, f[i] + g[i] - 1);
	printf("%d\n", n - maxn);
	return 0;
}
