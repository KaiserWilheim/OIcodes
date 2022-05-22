#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
ll p, a, b, x1, xn, v[N], c[N];
int tot, nxt[N], point[N];
void addline(ll z, ll mb)
{
	int x = z % N;
	++tot;
	nxt[tot] = point[x];
	point[x] = tot;
	v[tot] = z;
	c[tot] = mb;
}
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;
	}
	return res % p;
}
ll find(ll mb)
{
	int x = mb % N;
	for(int i = point[x]; i; i = nxt[i])
		if(v[i] == mb)return c[i];
	return -1;
}
ll bsgs(ll a, ll b, ll p)
{
	if(a % p == 0)return -1;
	tot = 0;
	memset(point, 0, sizeof(point));
	ll m = ceil(sqrt(p));
	ll am = qpow(a, m);
	for(int j = 0; j <= m; j++)
	{
		addline(b, j);
		b = (b * a) % p;
	}
	ll mul = 1;
	for(int i = 1; i <= m; i++)
	{
		mul = (mul * am) % p;
		ll t = find(mul);
		if(t != -1) return i * m - t + 1;
	}
	return -1;
}
int main()
{
	int T; scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld%lld", &p, &a, &b, &x1, &xn);
		if(x1 == xn)
		{
			printf("1\n");
			continue;
		}
		if(a == 0)
		{
			if(xn == b) printf("2\n");
			else printf("-1\n");
			continue;
		}
		if(a == 1 && b == 0)
		{
			printf("-1\n");
			continue;
		}
		if(a == 1)
		{
			ll nyb = qpow(b, p - 2);
			ll ans = ((((xn - x1) % p + p) % p) * nyb % p) % p;
			printf("%lld\n", ans + 1);
			continue;
		}
		ll inv = (b % p * qpow(a - 1, p - 2)) % p;
		ll fr = (xn % p + inv) % p;
		ll ed = (x1 % p + inv) % p;
		ed = qpow(ed, p - 2) % p;
		ll ans = bsgs(a, fr * ed % p, p);
		printf("%lld\n", ans);
	}
	return 0;
}
