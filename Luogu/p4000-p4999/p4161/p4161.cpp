#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, temp;
int prime[250];
ll f[1010];
bool vis[1010];

void get_prime()
{
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])
		{
			if(n < i * i)break;
			for(int j = i * i; j <= n; j += i)vis[j] = true;
		}
	}
	for(int i = 2; i <= n; i++)
		if(!vis[i])prime[++prime[0]] = i;
	return;
}

int main()
{
	scanf("%d", &n);
	if(n == 1)
	{
		puts("1");
		return 0;
	}
	get_prime();
	f[0] = 1;
	for(int i = 1; i <= prime[0]; i++)
	{
		for(int j = n; j >= prime[i]; j--)
		{
			temp = prime[i];
			while(temp <= j)
			{
				f[j] += f[j - temp];
				temp *= prime[i];
			}
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++)ans += f[i];
	printf("%lld\n", ans + 1);
	return 0;
}

