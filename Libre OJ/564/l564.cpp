#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int n;
	scanf("%d", &n);
	int half = n / 2;
	int res = (half * half) + ((n - half) * (n - half));
	printf("%d\n", res);
	for(int i = 1; i <= half; i++)
	{
		for(int j = 1; j <= half; j++)
		{
			int z = (j + i - 2) % half + 1;
			printf("%d %d %d\n", i, j, z);
		}
	}
	for(int i = 1; i <= (n - half); i++)
	{
		for(int j = 1; j <= (n - half); j++)
		{
			int z = (j + i - 2) % (n - half) + 1;
			printf("%d %d %d\n", i + half, j + half, z + half);
		}
	}
	return 0;
}
