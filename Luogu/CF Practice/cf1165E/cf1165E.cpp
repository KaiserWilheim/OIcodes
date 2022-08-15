#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
const ll mod = 998244353;
ll a[N], b[N];
ll n;
int main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		a[i] = (a[i] * i * (n - i + 1));
	}
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1, greater<ll>());
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		a[i] %= mod;
		ans = (ans + a[i] * b[i]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
