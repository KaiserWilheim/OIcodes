#include <bits/stdc++.h>
const int N = 10010;
int a[N];
using namespace std;
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);
		a[i] = k << 1;
	}
	for(int j = 1; j <= m; j++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[x] += z;
		a[y] += z;
	}
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for(int i = n; i >= 1; i -= 2)ans += a[i] - a[i - 1];
	printf("%d", ans / 2);
	return 0;
}
