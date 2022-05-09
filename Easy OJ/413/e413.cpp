#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	ll l, r;
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", r - l + 1);
	}
	return 0;
}
