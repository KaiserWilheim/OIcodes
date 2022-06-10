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
		f[i] = 1;
		g[i] = 1;
		scanf("%d", &a[i]);
		for(int j = 1; j < i; j++)
		{
			if(a[i] > a[j])
				f[i] = max(f[i], f[j] + 1);
			if(a[i] < a[j])
				g[i] = max(g[i], max(f[j] + 1, g[j] + 1));
		}
		maxn = max(maxn, max(f[i], g[i]));
	}
	printf("%d\n", maxn);
	return 0;
}
