#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 32010;
const ll mod = 1e9 + 7;
namespace Mker
{
	unsigned long long SA, SB, SC;
	void init() { scanf("%llu%llu%llu", &SA, &SB, &SC); }
	unsigned long long rand()
	{
		SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
		unsigned long long t = SA;
		SA = SB, SB = SC, SC ^= t ^ SA; return SC;
	}
}
ll a[N], pa[N];
ll b[N], pb[N];
int main()
{
	int T;
	scanf("%d", &T);
	Mker::init();
	int S = 32000;
	a[0] = pa[0] = 1;
	b[0] = pb[0] = 1;
	for(int i = 1; i <= S; i++)
	{
		a[i] = a[i - 1] * 94153035ll % mod;
		b[i] = b[i - 1] * 905847205ll % mod;
	}
	for(int i = 1; i <= S; i++)
	{
		pa[i] = pa[i - 1] * a[S] % mod;
		pb[i] = pb[i - 1] * b[S] % mod;
	}
	ll tres = 0;
	for(int i = 1; i <= T; i++)
	{
		int n = Mker::rand() % (mod - 1);
		ll res = (pa[n / S] * a[n % S] - pb[n / S] * b[n % S]) % mod;
		res = (res + mod) * 233230706ll % mod;
		tres ^= res;
	}
	printf("%lld\n", tres);
	return 0;
}
