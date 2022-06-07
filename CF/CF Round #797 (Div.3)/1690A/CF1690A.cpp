#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);
		int t = ceil(m / 3.0) + 1;
		int f = t - 1;
		if(m - f - t == 0)f--;
		printf("%d %d %d\n", f, t, m - f - t);
	}
	return 0;
}
