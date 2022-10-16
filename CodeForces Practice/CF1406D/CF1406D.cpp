#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
ll a[N];
ll b[N];
int main()
{
	scanf("%d", &n);
	ll sum = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		b[i] = a[i] - a[i - 1];
		if(i != 1 && b[i] > 0)sum += b[i];
	}
	ll ans = ceil((sum + a[1]) / 2.0);
	printf("%lld\n", ans);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int l, r;
		ll x;
		scanf("%d%d%lld", &l, &r, &x);
		r++;
		if(l != 1)sum -= max(0ll, b[l]) - max(0ll, b[l] + x);
		if(r != n + 1 && r != 1)sum -= max(0ll, b[r]) - max(0ll, b[r] - x);
		b[l] += x, b[r] -= x;
		ans = ceil((sum + b[1]) / 2.0);
		printf("%lld\n", ans);
	}
	return 0;
}