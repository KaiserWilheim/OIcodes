#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll l, r;
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", r - l + 1);
	}
	return 0;
}