#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 20010;
int n;
bool vis[N];
int prime[N];
void seive()
{
	for(int i = 2; i <= 10000; i++)
	{
		if(!vis[i])prime[++prime[0]] = i;
		for(int j = 1; j <= prime[0] && i * prime[j] <= 10000; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
ll left[N], rght[N];
int main()
{
	scanf("%d", &n);
	seive();
	for(int i = 1; i <= n; i++)
	{
		::left[i] = prime[(i & 1) ? ((i / 2) + 1) : (n * 2 - (i / 2) + 1)];
		rght[i] = prime[((i & 1) ? (n - (i / 2)) : (n + (i / 2))) + (n & 1)];
	}
	::left[0] = ::left[n + 1] = rght[0] = rght[n + 1] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			ll res;
			if((i + j) % 2 == 0)res = ::left[(i + j) / 2] * rght[(n + i - j + (n & 1)) / 2];
			else res = ::left[(i + j) / 2] * ::left[(i + j) / 2 + 1] * rght[(n + i - j + (n & 1)) / 2] * rght[(n + i - j + (n & 1)) / 2 + 1] + 1;
			printf("%lld ", res);
		}
		putchar('\n');
	}
	return 0;
}
