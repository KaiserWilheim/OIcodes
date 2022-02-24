#include<bits/stdc++.h>
using namespace std;
int a[110][110];

int main()
{
	int n;
	scanf("%d", &n);
	int m = (n * (n + 2) + (n & 1) - 2) / 2;
	printf("%d\n", m);
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int x = a[j][a[j][0]];
			if((!x) || ((int(sqrt(x + i)) * (int(sqrt(x + i)))) == x + i))
			{
				a[j][++a[j][0]] = i;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= a[i][0]; j++)
		{
			printf("%d ", a[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
