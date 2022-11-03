#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n, greater<int>());
	ll ans = 0, top = a[1] + 1;
	ll tot = 0;
	for(int i = 1; i <= n; i++)
	{
		tot += a[i];
		if(top > a[i])
		{
			ans += top - a[i];
			top = a[i];
		}
		else
		{
			ans++;
			if(top > 1)top--;
		}
	}
	ans += top - 1;
	printf("%lld\n", tot - ans);
	return 0;
}
