#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010;
int n, m;
ll maxn = 0;
ll a[N], b[N], p[N], bonus[N];
void exgcd(ll A, ll B, ll& x, ll& y, ll& gcd)
{
	if (!B) x = 1, y = 0, gcd = A;
	else exgcd(B, A % B, y, x, gcd), y -= (A / B) * x;
}
ll excrt()
{
	ll ans = 0, lcm = 1;
	ll x, y, gcd, A, B, C;
	for (int i = 1; i <= n; ++i)
	{
		A = (__int128)b[i] * lcm % p[i];
		B = p[i];
		C = (a[i] - b[i] * ans % p[i] + p[i]) % p[i];
		exgcd(A, B, x, y, gcd), x = (x % B + B) % B;
		if (C % gcd) return -1;
		ans += (__int128)(C / gcd) * x % (B / gcd) * lcm % (lcm *= B / gcd);
		ans %= lcm;
	}
	if (ans < maxn) ans += ((maxn - ans - 1) / lcm + 1) * lcm;
	return ans;
}
multiset<ll>s;
void solve()
{
	s.clear();
	maxn = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &p[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &bonus[i]);
	for (int i = 1; i <= m; i++)
	{
		ll x;
		scanf("%lld", &x);
		s.insert(x);
	}
	for (int i = 1; i <= n; ++i)
	{
		auto it = s.upper_bound(a[i]);
		if (it != s.begin()) it--;
		b[i] = *it;
		s.erase(it);
		s.insert(bonus[i]);
		maxn = max(maxn, (a[i] - 1) / b[i] + 1);
	}
	printf("%lld\n", excrt());
	return;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	return 0;
}
