#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e7 + 10;
int n, m;
int phi[N] = { 0,1 };
void getphi()
{
	for(int i = 2; i < N; i++) if(!phi[i])
		for(int j = i; j < N; j += i)
		{
			if(!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i * (i - 1);
		}
}
ll qpow(ll a, ll x, ll p)
{
	ll res = 1ll;
	while(x)
	{
		if(x & 1ll)res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1ll;
	}
	return res;
}
ll work(ll p)
{
	if(p == 1ll)return 0;
	int k = 0;
	while(!(p & 1ll))
	{
		p /= 2;
		k++;
	}
	return qpow(2ll, (work(phi[p]) % phi[p] - k % phi[p] + phi[p]) % phi[p] + phi[p], p) << k;
}
int main()
{
	getphi();
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ll p;
		scanf("%lld", &p);
		printf("%lld\n", work(p));
	}
	return 0;
}
