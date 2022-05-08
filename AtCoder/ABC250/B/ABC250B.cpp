#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=a;j++)
		{
			for(int k = 1; k <= n; k++)
				for(int l = 1; l <= b; l++)
					if((i + k) & 1)putchar('#');
					else putchar('.');
			putchar('\n');
		}	
	return 0;
}
