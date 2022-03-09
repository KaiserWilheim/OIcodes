#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a, b, ans, sum, t;
int main()
{
	scanf("%lld %lld", &a, &b);
	if(a > b)swap(a, b);
	t = (a - 1) * b / a - 1;
	sum = (sum + (a - 1) * b) % a;
	printf("%lld", t * a + sum);
	return 0;
}
