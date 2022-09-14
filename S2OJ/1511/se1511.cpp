#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll mod = 998244353;
ll qpow(ll a, int x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
int n;
int a[N];
ll fac[N], inv[N];
ll cnt1, cnt5, cnt7;
ll cnt2, cnt3, cnt6;
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	fac[0] = 1;
	for(int i = 1; i <= 1000000; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[1000000] = qpow(fac[1000000], mod - 2);
	for(int i = 999999; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	ll ans = 1;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == 1)cnt1++;
		else if(a[i] == 5)cnt5++;
		else if(a[i] == 7)cnt7++;
		else if(a[i] == 2 || a[i] == 4 || a[i] == 8)
		{
			cnt2++;
			cnt6++;
		}
		else if(a[i] == 3 || a[i] == 9)
		{
			cnt3++;
			cnt6++;
		}
		else if(a[i] == 6)
		{
			cnt6++;
			ans = ans * fac[cnt2 + cnt3] % mod * inv[cnt2] % mod * inv[cnt3] % mod;
			cnt2 = cnt3 = 0;
		}
	}
	ans = ans * fac[cnt2 + cnt3] % mod * inv[cnt2] % mod * inv[cnt3] % mod;
	ans = ans * fac[cnt1 + cnt6 + cnt5 + cnt7] % mod * inv[cnt1] % mod * inv[cnt6] % mod * inv[cnt5] % mod * inv[cnt7] % mod;
	cout << ans << endl;
	return 0;
}