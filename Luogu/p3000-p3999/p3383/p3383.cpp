#include <bits/stdc++.h>
using namespace std;
const int N = 100000010, M = 1000010;
int prime[N >> 4];
bool vis[N];
int qwert[M];
int idx = 1;
int n, m;
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)scanf("%d", &qwert[i]);
	prime[0] = 0;
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
	for(int i = 1; i <= prime[0]; i++)
	{
		if(n % prime[i] == 0)
		{
			vis[n] = true;
			break;
		}
		prime[0]++;
		prime[prime[0]] = n;
	}
	for(int i = 1; i <= m; i++)
	{
		printf("%d\n", prime[qwert[i]]);
	}
	return 0;
}
