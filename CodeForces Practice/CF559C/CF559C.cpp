#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2020, M = 1000000, MAX = 1000010, mod = 1e9 + 7;
struct node
{
	int x, y;
	friend bool operator < (const node &x, const node &y)
	{
		if(x.x == y.x) return x.y < y.y;
		return x.x < y.x;
	}
}a[N];
int n, h, w;
ll f[N], fac[MAX], inv[MAX];
inline ll qpow(ll x, ll ent)
{
	ll ans = 1;
	while(ent)
	{
		if(ent & 1) ans = ans * x % mod;
		ent >>= 1;
		x = x * x % mod;
	}
	return ans % mod;
}
inline ll C(ll x, ll y)
{
	if(x < y) return 0;
	return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

int main()
{
	scanf("%d%d%d", &h, &w, &n);
	h = h - 1; w = w - 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].x -= 1; a[i].y -= 1;
	}
	a[0].x = a[0].y = 0;
	a[++n].x = h; a[n].y = w;
	sort(a + 1, a + n + 1);
	fac[0] = 1;
	for(ll i = 1; i <= M; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[0] = 1; inv[M] = qpow(fac[M], mod - 2);
	for(ll i = M - 1; i >= 1; i--)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	for(int i = 1; i <= n; i++)
	{
		f[i] = C(a[i].x + a[i].y, a[i].x);
		if(f[i] == 0) continue;
		for(int j = 1; j < i; j++)
		{
			f[i] -= (f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x)) % mod;
			f[i] %= mod;
			f[i] += mod; f[i] %= mod;
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}
