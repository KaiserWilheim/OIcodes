#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
ll w[N], sum;
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		sum = 0;
		int n, k;
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++)
		{
			scanf("%lld", &w[i]);
			sum += w[i];
		}
		for(int i = 1; i <= n; i++)
			printf("%lf ", w[i] + w[i] * k * 1.0 / sum);
		putchar('\n');
	}
	return 0;
}
