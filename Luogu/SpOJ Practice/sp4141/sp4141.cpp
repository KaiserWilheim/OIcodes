#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 5;
int phi[N], prime[N];
bool visit[N];
void getphi(int n)
{
	phi[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		if(!visit[i])
		{
			prime[prime[0] + 1] = i;
			prime[0]++;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			visit[i * prime[j]] = true;
			if(!(i % prime[j]))
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
}
int main()
{
	getphi(1000000);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		printf("%d\n", phi[x]);
	}
	return 0;
}