#include<bits/stdc++.h>
#define ll long long
using namespace std;
double a, b, c, x;
int main()
{
	scanf("%lf%lf%lf%lf", &a, &b, &c, &x);
	double ans = 0;
	if(x <= a)
	{
		ans = 1;
	}
	else if(x > b)
	{
		ans = 0;
	}
	else
	{
		ans = c / (b - a);
	}
	printf("%.10lf\n", ans);
	return 0;
}
