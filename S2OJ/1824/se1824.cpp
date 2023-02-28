#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
const ull mod = (1ull << 63) - 1;
ull sum1(ll x)
{
	ull i = x, j = x + 1;
	if(i & 1)return i * (j >> 1);
	return (i >> 1) * j;
}
ull sum2(ll x)
{
	ull i = x, j = x + 1, k = 2 * x + 1;
	if(i & 1)j >>= 1;
	else i >>= 1;
	if(i % 3 == 0)i /= 3;
	else if(j % 3 == 0)j /= 3;
	else k /= 3;
	return i * j * k;
}
ull sum3(ll x)
{
	return sum1(x) * sum1(x);
}
ull calc1(ll x)
{
	if(x < 0)return 0;
	return sum3(x) * 8 + sum2(x) * 16 + sum1(x) * 11 + 3ull * (x + 1);
}
ull calc2(ll x, ll y)
{
	ull tmp = sum2(y) * 8 + sum1(y) * 6 + 1ull * (x + 2) * (y - x + 1);
	if(x > 0)tmp -= sum2(x - 1) * 8 + sum1(x - 1) * 6;
	if(tmp & 1)return tmp * ((x + 1) >> 1);
	return (tmp >> 1) * (x + 1);
}
ull calc3(ll x, ll y)
{
	ull tmp = sum2(x) * 8 - sum1(x) * 6 - 1ull * (y - 2) * (x - y - 1);
	if(y > 0)tmp -= sum2(y + 1) * 8 - sum1(y + 1) * 6;
	if(tmp & 1)return tmp * ((y + 1) >> 1);
	return (tmp >> 1) * (y + 1);
}
ull solve(ll x, ll y)
{
	if(x < 0 || y < 0)return 0;
	if(x <= y + 1)return calc1(x - 1) + calc2(x, y);
	else return calc1(y) + calc3(x, y);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll l, r, t, b;
		scanf("%lld%lld%lld%lld", &l, &r, &t, &b);
		ull res = solve(r, b) - solve(l - 1, b) - solve(r, t - 1) + solve(l - 1, t - 1);
		res = res & mod;
		printf("%llu\n", res);
	}
	return 0;
}
