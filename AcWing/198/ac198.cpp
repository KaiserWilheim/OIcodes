#include<bits/stdc++.h>
using namespace std;
#define ll long long
int primes[9] = { 2,3,5,7,11,13,17,19,23 };
int maxd;
int num;
int n;

void dfs(int u, int last, int p, int s)
{
	if((s > maxd) || ((s == maxd) && (p < num)))
	{
		maxd = s;
		num = p;
	}
	if(u == 9)return;
	for(int i = 1; i <= last; i++)
	{
		if(( ll )p * primes[u] > n)break;
		p *= primes[u];
		dfs(u + 1, i, p, s * (i + 1));
	}
}

int main()
{
	scanf("%d", &n);
	dfs(0, 30, 1, 1);
	printf("%d\n", num);
	return 0;
}
