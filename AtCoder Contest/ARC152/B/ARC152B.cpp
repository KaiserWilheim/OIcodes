#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n;
ll m;
ll a[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] *= 2;
	}
	ll ans = 1e15;
	for(int i = 1; i <= n; i++)
	{
		ll pos = 2 * m - a[i];
		int k = upper_bound(a + 1, a + 1 + n, pos) - a - 1;
		if(k != 0)ans = min(ans, pos - a[k]);
		if(k != n)ans = min(ans, a[k + 1] - pos);
	}
	printf("%lld\n", ans + m * 2);
	return 0;
}
