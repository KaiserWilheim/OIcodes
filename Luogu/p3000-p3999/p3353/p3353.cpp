#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int a[N];
int main()
{
	int n, w;
	int maxn = 0;
	scanf("%d%d", &n, &w);
	for(int i = 1; i <= n; i++)
	{
		int x, k;
		scanf("%d%d", &x, &k);
		a[x] += k;
		maxn = max(maxn, x);
	}
	for(int i = 1; i <= maxn; i++)a[i] += a[i - 1];
	int ans = 0;
	for(int i = 1 + w; i <= maxn; i++)
		ans = max(ans, a[i] - a[i - w]);
	printf("%d\n", ans);
	return 0;
}
