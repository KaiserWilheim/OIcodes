#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
ll read()
{
	ll x = 0, flag = 1;
	char c = getchar();
	while(c != '-' && !(c >= '0' && c <= '9'))c = getchar();
	if(c == '-')flag = -1, c = getchar();
	while(c >= '0' && c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * flag;
}
ll n, a[N];
ll l[N], r[N];
ll h[N], tt;
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i <= n; i++)
	{
		ll cur = tt;
		while(cur && a[h[cur]] > a[i])cur--;
		if(cur)r[h[cur]] = i;
		if(cur < tt)l[i] = h[cur + 1];
		h[++cur] = i;
		tt = cur;
	}
	ll ansl = 0, ansr = 0;
	for(ll i = 1; i <= n; i++)
	{
		ansl ^= i * (l[i] + 1);
		ansr ^= i * (r[i] + 1);
	}
	printf("%lld %lld\n", ansl, ansr);
	return 0;
}
