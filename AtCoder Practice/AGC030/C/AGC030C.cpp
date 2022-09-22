#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int k;
int n;
int ans[N][N];
int main()
{
	scanf("%d", &k);
	if(k == 1)
	{
		printf("1\n1\n");
		return 0;
	}
	n = (k % 4 == 0) ? k / 4 : k / 4 + 1;
	n *= 2;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			ans[i][j] = ((i + j) % n) + ((i % 2 == 1) ? n : 0);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(ans[i][j] >= k)ans[i][j] -= n;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			printf("%d ", ans[i][j] + 1);
		putchar('\n');
	}
	return 0;
}