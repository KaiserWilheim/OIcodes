#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
ll n;
double a[N], avg[N], sum[N], minn[N];
double maxn;
int main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n + 1; i++)minn[i] = 10010;
	for(int i = 1; i <= n; i++)scanf("%lf", &a[i]);
	for(int i = n; i >= 2; i--)
	{
		minn[i] = min(minn[i + 1], a[i]);
		sum[i] = sum[i + 1] + a[i];
		if(i != n)avg[i] = (sum[i] - minn[i]) / ( double )(n - i);
	}
	for(int i = 2; i < n; i++)maxn = max(maxn, avg[i]);
	for(int i = 2; i < n; i++)
		if(maxn == avg[i])
			printf("%lld\n", i - 1);
	return 0;
}
