#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		int res = (n % m) ? n / m + 1 : n / m;
		res = n - res;
		printf("%d\n", (res % 2) ^ 1);
	}
	return 0;
}
