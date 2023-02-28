#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
int n, m;
ll a[N];
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int main()
{
	scanf("%d%d", &n, &m);
	ll sum = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum = add(sum, a[i]);
	}
	sum = sum * n % mod;
	ll tmp1 = 0, tmp2 = 0;
	for(int i = 1; i <= n; i++)
	{
		tmp1 = add(tmp1, a[i] * (n - i + 1) % mod);
		tmp2 = add(tmp2, a[i] * i % mod);
	}
	if(m == 0)
	{
		printf("%lld\n", tmp1);
		return 0;
	}
	ll res1 = add(tmp1, add(tmp2, sum)) * qpow(2, m - 1) % mod;
	ll res2 = add(tmp1, add(tmp1, sum)) * qpow(2, m - 1) % mod;
	ll tmp3 = sum * (add(qpow(2, m - 1), mod - 1) * qpow(2, m) % mod) % mod;
	res1 = add(res1, tmp3), res2 = add(res2, tmp3);
	printf("%lld\n", max(res1, res2));
	return 0;
}
