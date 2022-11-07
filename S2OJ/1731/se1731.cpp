#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
const int mod = 1e9 + 7;
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
int a[N], pr[N];
ll f[N];
ll k[N], b[N];
int main()
{
	string s;
	cin >> s;
	n = s.length();
	for(int i = 1; i <= n; i++)
		a[i] = s[i - 1] - '0';
	for(int i = 2; i <= n; i++)
	{
		int j = pr[i - 1];
		while(j && a[i] != a[j + 1])j = pr[j];
		if(a[i] == a[j + 1])j++;
		pr[i] = j;
	}
	k[0] = 1, b[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		k[i] = 2 * k[i - 1] % mod;
		b[i] = 2 * b[i - 1] % mod;
		int j = i - 1;
		while(j && a[i] == a[j + 1])j = pr[j];
		if(a[i] != a[j + 1])j++;
		k[i] = (k[i] - k[j] + mod) % mod;
		b[i] = ((b[i] - b[j] - 2) % mod + mod) % mod;
	}
	ll res = (mod - b[n]) * qpow(k[n], mod - 2) % mod;
	printf("%lld\n", res);
	return 0;
}