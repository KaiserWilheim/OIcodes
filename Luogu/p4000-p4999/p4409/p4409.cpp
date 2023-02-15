#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 20010, M = 10010;
int n;
ll a[N];
ll ceil(ll a, ll b)
{
	if(a % b)return a / b + 1;
	return a / b;
}
int main()
{
	scanf("%d", &n);
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		res += a[i];
	}
	if(n == 1)
	{
		printf("%lld\n", a[n]);
		return 0;
	}
	a[0] = a[n];
	res = ceil(res, n / 2);
	for(int i = 1; i <= n; i++)
		res = max(res, a[i] + a[i - 1]);
	printf("%lld\n", res);
	return 0;
}
