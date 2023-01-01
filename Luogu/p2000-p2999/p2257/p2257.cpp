#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010, M = 700010;
int prime[M];
bool vis[N];
ll mu[N], f[N], sum[N];
void seive()
{
	mu[1] = 1;
	for(int i = 2; i <= 10000000; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= 10000000; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= prime[0]; i++)
		for(int j = 1; j * prime[i] <= 10000000; j++)
			f[j * prime[i]] += mu[j];
	for(int i = 1; i <= 10000000; i++)
		sum[i] = sum[i - 1] + f[i];
}
ll solve(int n, int m)
{
	ll res = 0;
	if(n > m)swap(n, m);
	for(int l = 1, r = 0; l <= n; l = r + 1)
	{
		r = min(n / (n / l), m / (m / l));
		res += (sum[r] - sum[l - 1]) * (n / l) * (m / l);
	}
	return res;
}
int main()
{
	seive();
	int T;
	int n, m;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		printf("%lld\n", solve(n, m));
	}
	return 0;
}
