#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
ll n;
ll a, b;
void solve()
{
	scanf("%lld%lld%lld", &n, &a, &b);
	if(b == 1)
	{
		puts("Yes");
		return;
	}
	if(a == 1)
	{
		if(n % b == 1)puts("Yes");
		else puts("No");
		return;
	}
	for(ll i = 1; i <= n; i *= a)
	{
		ll k = n - i;
		if(k % b == 0)
		{
			puts("Yes");
			return;
		}
	}
	puts("No");
	return;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}