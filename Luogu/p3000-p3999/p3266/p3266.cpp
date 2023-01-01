#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3000010;
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
ll fac[N], inv[N];
ll calc(ll x, ll y)
{
	if(x < 0 || y < 0)return 0;
	else return fac[x + y] * inv[x] % mod * inv[y] % mod;
}
void flip1(ll &x, ll &y)
{
	swap(x, y);
	x--, y++;
}
void flip2(ll &x, ll &y)
{
	swap(x, y);
	x += m + 2, y -= m + 2;
}
int main()
{
	scanf("%d%d", &n, &m);
	fac[0] = 1;
	int maxn = max(n, m) * 3 + 1;
	for(int i = 1; i <= maxn; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1; inv[maxn] = qpow(fac[maxn], mod - 2);
	for(int i = maxn; i > 1; i--)
		inv[i - 1] = inv[i] * i % mod;
	ll x = m + n + 1, y = n, ans = calc(x, y);
	while(x >= 0 && y >= 0)
	{
		flip1(x, y); ans = (ans - calc(x, y) + mod) % mod;
		flip2(x, y); ans = (ans + calc(x, y));
	}
	x = m + n + 1, y = n;
	while(x >= 0 && y >= 0)
	{
		flip2(x, y); ans = (ans - calc(x, y) + mod) % mod;
		flip1(x, y); ans = (ans + calc(x, y));
	}
	printf("%lld\n", ans);
	return 0;
}
