#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
#define ll long long
ll h[N];
int main()
{
	ll m, n;
	scanf("%lld%lld", &n, &m);
	ll maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &h[i]);
		maxn = max(maxn, h[i]);
	}
	ll l = 0, r = maxn;
	while(l <= r)
	{
		ll mid = l + (r - l) / 2;
		ll sum = 0ll;
		for(int i = 1; i <= n; i++)
			sum += max(0ll, h[i] - mid);
		if(sum < m)r = mid - 1;
		else l = mid + 1;
	}
	cout << r << endl;
	return 0;
}
