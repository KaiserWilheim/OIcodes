#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010, M = 700010;
ll mod;
bool vis[N];
int prime[M];
ll inv[N], fac[N];
ll ppi[M], pinv[M];
int psum[N];
void init()
{
	vis[0] = vis[1] = true;
	for(int i = 2; i <= 10000000; i++)
	{
		if(!vis[i])prime[++prime[0]] = i;
		for(int j = 1; j <= prime[0] && i * prime[j] <= 10000000; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
	inv[1] = 1;
	for(int i = 2; i < mod && i <= 10000000; i++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	ppi[0] = 1;
	for(int i = 1; i <= prime[0]; i++)ppi[i] = ppi[i - 1] * (prime[i] - 1) % mod;
	pinv[0] = 1;
	for(int i = 1; i <= prime[0]; i++)
	{
		if(prime[i] != mod)pinv[i] = pinv[i - 1] * inv[prime[i] % mod] % mod;
		else pinv[i] = pinv[i - 1];
	}
	fac[0] = 1;
	for(int i = 1; i <= 10000000; i++)
	{
		if(i != mod)fac[i] = fac[i - 1] * i % mod;
		else fac[i] = fac[i - 1];
	}
	for(int i = 2; i <= 10000000; i++)
	{
		if(vis[i])psum[i] = psum[i - 1];
		else psum[i] = psum[i - 1] + 1;
	}
}
int n, m;
int main()
{
	int T;
	scanf("%d%lld", &T, &mod);
	init();
	while(T--)
	{
		scanf("%d%d", &n, &m);
		if(n >= mod && m < mod)
		{
			puts("0");
			continue;
		}
		printf("%lld\n", fac[n] * ppi[psum[m]] % mod * pinv[psum[m]] % mod);
	}
	return 0;
}
