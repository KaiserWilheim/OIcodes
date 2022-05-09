#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e7 + 5;
int phi[N], prime[N / 100];
bool vis[N];
void getphi(int n)
{
	phi[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])
		{
			prime[prime[0] + 1] = i;
			prime[0]++;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = true;
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
	int T;
	getphi(1200);
	scanf("%d", &T);
	for(int TT=1;TT<=T;TT++)
	{
		int n;
		scanf("%d", &n);
		int ans = 0;
		for(int i = 2; i <= n; i++)ans += phi[i];
		ans = ans * 2 + 3;
		printf("%d %d %d\n", TT, n, ans);
	}
	return 0;
}
