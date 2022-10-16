#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 998244353;
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
int n;
string s;
ll fac[N], inv[N];
ll C(int n, int m)
{
	if(n < m)return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void init()
{
	fac[0] = 1;
	for(int i = 1; i <= 100000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[0] = 1, inv[100000] = qpow(fac[100000], mod - 2);
	for(int i = 99999; i >= 1; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}
int main()
{
	init();
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n >> s;
		int cnt0 = 0, cnt11 = 0;
		for(int i = 0; i < n; i++)
		{
			if(s[i] == '0')cnt0++;
			if(i > 0 && s[i] == '1' && s[i - 1] == '1')
			{
				cnt11++;
				s[i] = '0';
			}
		}
		ll res = C(cnt0 + cnt11, cnt11);
		printf("%lld\n", res);
	}
	return 0;
}