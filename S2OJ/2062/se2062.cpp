#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d", &n);
	if(n & 1)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n / 2; j++)
			{
				int u = (i - j + n) % n + 1,
					v = (i + j + 1) % n + 1;
				if(u > v)swap(u, v);
				printf("%d %d\n", u, v);
			}
		}
	}
	else
	{
		for(int i = 0; i < n - 1; i++)
		{
			for(int j = 0; j < n / 2 - 1; j++)
			{
				int u = (i - j + (n - 1)) % (n - 1) + 1,
					v = (i + j + 1) % (n - 1) + 1;
				if(u > v)swap(u, v);
				printf("%d %d\n", u, v);
			}
			printf("%d %d\n", (i + n / 2) % (n - 1) + 1, n);
		}
	}
	return 0;
}
