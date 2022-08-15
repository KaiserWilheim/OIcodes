#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n, k, a, b, c;
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= k; i++)
			scanf("%d%d%d", &a, &b, &c);
		if((n + k) & 1)puts("YES");
		else puts("NO");
	}
	return 0;
}
