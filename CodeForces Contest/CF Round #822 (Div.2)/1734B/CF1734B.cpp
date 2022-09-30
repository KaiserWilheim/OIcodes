#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n;
void solve()
{
	scanf("%d", &n);
	puts("1");
	for(int i = 2; i <= n; i++)
	{
		printf("1 ");
		for(int j = 2; j < i; j++)
			printf("0 ");
		printf("1\n");
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}