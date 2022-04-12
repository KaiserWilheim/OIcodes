#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int a = 0, b = 0;
	for(int i = 1; i <= 3; i++)
	{
		int c, d;
		scanf("%d%d", &c, &d);
		a ^= c, b ^= d;
	}
	printf("%d %d\n", a, b);
	return 0;
}
