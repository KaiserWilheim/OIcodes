#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
const ll inv = 5e8 + 4;
ll sum(ll x)
{
	ll res = (x + 1) % mod * x % mod * inv % mod;
	return res;
}
ll lg[110], q[110];
int main()
{
	lg[1] = 1;
	for(int i = 2; i < 64; i++)
	{
		lg[i] = lg[i - 1] << 1;
		q[i] = sum(((1ll << (i - 1)) - 1) % mod);
		q[i] = (q[i] + q[i - 1]) % mod;
	}
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll n;
		scanf("%lld", &n);
		ll cnt = 0;
		for(cnt = 63; cnt >= 1; cnt--)
			if(n > lg[cnt])break;
		n -= (1ll << (cnt - 1));
		ll ans = q[cnt - 1];
		ans = (ans + sum(n % mod)) % mod;
		ans = (ans * 2) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
