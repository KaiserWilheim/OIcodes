#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
const double eps = 1e-6;
int n;
int a[N];
ll sum[N];
bool chq(double mid)
{
	int j = 1;
	for(int i = 1; i <= n; i++)
	{
		while(i - j > n - i)j++;
		while(j < i && 1.0 * a[j] + 1.0 *a[n - (i - j) + 1] < 2.0 * (mid + 1.0 * a[i]))j++;
		if(sum[i] - sum[j - 1] + sum[n] - sum[n - (i - j)] >= (2 * (i - j) + 1) * (mid + 1.0 * a[i]))return true;
	}
	return false;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	double l = -1e6, r = 1e6;
	while(r - l >= eps)
	{
		double mid = (l + r) / 2;
		if(chq(mid))l = mid;
		else r = mid;
	}
	printf("%.5lf\n", l);
	return 0;
}
