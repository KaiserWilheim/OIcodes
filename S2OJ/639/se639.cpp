#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
const ll mod = 998244353;
ll add(ll a, ll b) { return a + b >= mod ? (a + b - mod) : (a + b); }
ll sub(ll a, ll b) { return add(a, mod - b); }
ll mul(ll a, ll b) { return 1ll * a * b % mod; }
ll qpow(ll a, ll b = mod - 2)
{
	ll c = 1;
	while(b)
	{
		if(b & 1) c = mul(c, a);
		a = mul(a, a);
		b >>= 1;
	}
	return c;
}

ll inv2 = qpow(2);
char s[N];
ll g1[62][62], g2[62][62];
ll f1[N][62];
ll cnt[62], buk[62], tot;
int to(char c)
{
	if(c >= 'A' && c <= 'Z') return c - 'A';
	if(c >= 'a' && c <= 'z') return c - 'a' + 26;
	return c - '0' + 52;
}
int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	memset(buk, -1, sizeof buk);
	for(int i = 1; i <= n; ++i)
	{
		int c = to(s[i]);
		if(buk[c] == -1) buk[c] = tot++;
	}
	for(int i = 1; i <= n; ++i)
	{
		int c = buk[to(s[i])];
		for(int j = 0; j < tot; ++j)
			f1[i][j] = f1[i - 1][j];
		f1[i][c] ++;
	}
	ll ans = 0;
	for(int i = n; i >= 3; --i)
	{
		int d = buk[to(s[i])];
		for(int c = 0; c < tot; ++c)
		{
			if(c == d) continue;
			g2[d][c] = add(g2[d][c], g1[c][d]);
		}
		int c = buk[to(s[i])];
		ll cur = i - 1, sum = 0;
		for(int d = 0; d < tot; ++d)
		{
			sum = add(sum, f1[i - 1][d] * f1[i - 1][d] % mod);
			if(c == d) continue;
			g1[c][d] = add(g1[c][d], cnt[d]);
		}
		cnt[c]++;
		c = buk[to(s[i])];
		for(int d = 0; d < tot; ++d)
		{
			ll tmp = cur;
			tmp = add(tmp, mod - f1[i - 1][c] - f1[i - 1][d]);
			tmp = tmp * tmp % mod;
			tmp = add(tmp, f1[i - 1][c] * f1[i - 1][c] % mod);
			tmp = add(tmp, f1[i - 1][d] * f1[i - 1][d] % mod);
			tmp = add(tmp, mod - sum);
			tmp = tmp * inv2 % mod;
			ans = add(ans, tmp * g2[d][c] % mod);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
