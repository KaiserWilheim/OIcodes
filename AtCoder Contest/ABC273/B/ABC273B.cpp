#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
ll n, m;
int main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		if(n % 10 >= 5)n = n / 10 + 1;
		else n = n / 10;
	}
	for(int i = 1; i <= m; i++)n *= 10;
	printf("%lld\n", n);
	return 0;
}