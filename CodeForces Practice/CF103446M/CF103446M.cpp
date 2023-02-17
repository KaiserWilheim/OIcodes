#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
signed main()
{
	scanf("%d", &n);
	double res = n * ((n + 1) >> 1) * ((n + 2) >> 1);
	res = 1 / res;
	printf("%.9lf", res);
	return 0;
}
