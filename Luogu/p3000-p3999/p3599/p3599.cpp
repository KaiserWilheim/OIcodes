#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
void solve1()
{
	scanf("%d", &n);
	if((n & 1) && (n != 1))
	{
		puts("0");
		return;
	}
	printf("2");
	for(int i = 1; i <= n; i++)
	{
		if(i & 1)printf(" %d", n - i + 1);
		else printf(" %d", i - 1);
	}
	putchar('\n');
}
int prime[N];
bool vis[N];
void seive()
{
	int lim = 100000;
	for(int i = 2; i <= lim; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= lim; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
ll qpow(ll a, ll x, ll mod)
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
void solve2()
{
	scanf("%d", &n);
	if(vis[n] && (n != 1) && (n != 4))
	{
		puts("0");
		return;
	}
	if(n == 1)
	{
		puts("2 1");
		return;
	}
	if(n == 4)
	{
		puts("2 1 3 2 4");
		return;
	}
	printf("2");
	ll tmp = 1, sum = 1;
	for(int i = 1; i <= n - 1; i++)
	{
		printf(" %lld", tmp);
		tmp = 1ll * qpow(sum, n - 2, n) * (i + 1) % n;
		sum = 1ll * sum * tmp % n;
	}
	printf(" %d\n", n);
}
int main()
{
	int id, T;
	scanf("%d%d", &id, &T);
	if(id == 2)
	{
		seive();
	}
	while(T--)
	{
		if(id == 1)solve1();
		else solve2();
	}
	return 0;
}
