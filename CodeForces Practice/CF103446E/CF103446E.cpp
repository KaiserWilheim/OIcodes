#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, k;
int a[N];
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	int prev = -1e9, ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] - prev >= k)
			prev = a[i], ans++;
	}
	printf("%d\n", ans);
	return 0;
}
