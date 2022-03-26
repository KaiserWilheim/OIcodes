#include<bits/stdc++.h>
using namespace std;
int a[110];
int main()
{
	int n, tot = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tot += a[i];
	}
	int avg = tot / n;
	int ans = 0;
	for(int i = 1; i < n; i++)
	{
		if(a[i] != avg)
		{
			ans++;
			a[i + 1] += (a[i] - avg);
		}
	}
	printf("%d\n", ans);
	return 0;
}

