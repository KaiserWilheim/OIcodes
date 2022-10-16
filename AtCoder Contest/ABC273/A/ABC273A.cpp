#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int main()
{
	scanf("%d", &n);
	ll ans = 1;
	for(int i = 1; i <= n; i++)
		ans *= i;
	printf("%lld\n", ans);
	return 0;
}