#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int phi[N], prime[N / 100];
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

int a[N];
int main()
{
	int T;
	scanf("%d", &T);
	int maxn = 0;
	for(int i = 1; i <= T; i++)
	{
		scanf("%d", &a[i]);
		maxn = max(maxn, a[i]);
	}
	getphi(maxn + 1);
	for(int i = 1; i <= T; i++)
		printf("%d\n", phi[a[i]]);
	return 0;
}
