#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int main()
{
	scanf("%d", &n);
	if(n == 2)puts("10");
	else if(n == 3)puts("Unlucky");
	else
	{
		if(n & 1)
		{
			printf("10001");
			n -= 5;
		}
		int k = n / 2;
		for(int i = 1; i <= k / 2; i++)
			printf("1001");
		if(k & 1)
			printf("10");
		putchar('\n');
	}
	return 0;
}
