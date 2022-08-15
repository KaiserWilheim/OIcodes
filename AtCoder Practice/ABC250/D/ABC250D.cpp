#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010;
bool vis[N];
ll primes[N];
void estseive()
{
	ll k = 1e6 + 1;
	for(ll i = 2; i <= k; i++)
	{
		if(vis[i])continue;
		primes[++primes[0]] = i;
		for(ll j = i * i; j <= k; j += i)
			vis[j] = true;
	}
}
ll f(ll p, ll q)
{
	double res = 1;
	res = (q * q * q);
	res *= p;
	if(res > 4e18)return 4e18;
	return p * q * q * q;
}
int main()
{
	estseive();
	ll n;
	cin >> n;
	ll res = 0;
	int q = primes[0];
	for(int p = 1; p <= primes[0]; p++)
	{
		while(p<q && f(primes[p], primes[q])>n)q--;
		if(p >= q)break;
		res += (q - p);
	}
	cout << res << endl;
	return 0;
}
