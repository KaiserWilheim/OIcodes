#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
double a[N];
double x[N], xx[N], ans[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &a[i]);
		x[i] = (x[i - 1] + 1.0) * a[i];
		xx[i] = (xx[i - 1] + 2.0 * x[i - 1] + 1) * a[i];
		ans[i] = ans[i - 1] + (3 * xx[i - 1] + 3 * x[i - 1] + 1) * a[i];
	}
	printf("%.15lf\n", ans[n]);
	return 0;
}
