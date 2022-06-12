#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
ll a[N];
ll sum[N];
ll tot;
int idx;
map<ll, int>dic;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		if(!dic.count(a[i]))dic.insert(make_pair(a[i], ++idx));
		int k = dic.find(a[i])->second;
		sum[k] += a[i];
		tot += a[i];
	}
	for(int i = 2; i <= idx; i++)
		sum[i] += sum[i - 1];
	while(m--)
	{
		ll x;
		scanf("%lld", &x);
		if(x >= a[n])
		{
			printf("%lld\n", (x * n) - tot);
			continue;
		}
		else if(x <= a[1])
		{
			printf("%lld\n", tot - (x * n));
			continue;
		}
		int k = upper_bound(a + 1, a + 1 + n, x) - a - 1;
		int r = dic.find(a[k])->second;
		ll res = 0;
		res += (x * k) - sum[r];
		res += (tot - sum[r]) - (x * (n - k));
		printf("%lld\n", res);
	}
	return 0;
}
