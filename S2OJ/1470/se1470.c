#include<stdio.h>
int n, k;
long long a[100010], s[100010];
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++)scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];
	long long m = 1e18;
	for(int i = k; i < n; i++)m = m < (s[i] - s[i - k]) ? m : (s[i] - s[i - k]);
	printf("%lld\n", m);
	return 0;
}