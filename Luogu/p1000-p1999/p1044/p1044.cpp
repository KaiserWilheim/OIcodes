#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d", &n);
	long long ans = 1;
	for(int i = 1; i <= n; i++)
		ans = ans * (4 * i - 2) / (i + 1);
	printf("%lld\n", ans);
	return 0;
}
