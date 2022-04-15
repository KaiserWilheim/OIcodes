#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int a[N];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	ll ans = 0;
	for(int i = 1; i <= n + 1; i++)
		if(a[i] < a[i - 1])ans += a[i - 1] - a[i];
	printf("%lld\n", ans);
	return 0;
}
