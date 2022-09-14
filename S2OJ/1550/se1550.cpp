#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int a[N], tmp[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	ll ans = 0;
	for(int i = 1; i < n; i++)
	{
		if(a[i] == n)break;
		if(a[i] > a[i + 1])
		{
			ans++;
			swap(a[i], a[i + 1]);
		}
	}
	ans += 1ll * n * (n - 1);
	ans -= (n >= 3 && tmp[1] == n - 1 && tmp[n] == n);
	printf("%lld\n", ans);
	return 0;
}