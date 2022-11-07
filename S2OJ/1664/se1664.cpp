#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n, m;
int sum[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l--;
		int k = 0;
		for(int d = 1; d <= r; d = k + 1)
		{
			if(l / d == 0)k = r;
			else k = min(l / (l / d), r / (r / d));
			if(r / d - l / d > 0)sum[d]++, sum[k + 1]--;
		}
	}
	for(int i = 1; i <= m; i++)
	{
		sum[i] += sum[i - 1];
		printf("%d\n", sum[i]);
	}
	return 0;
}