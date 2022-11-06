#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N];
int cnt2[N], cnt3[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		while(a[i] % 2 == 0)
		{
			cnt2[i]++, a[i] /= 2;
		}
		while(a[i] % 3 == 0)
		{
			cnt3[i]++, a[i] /= 3;
		}
	}
	bool flag = true;
	for(int i=1;i<=n;i++)
	{
		if(a[i] != a[1])
		{
			flag = false;
			break;
		}
	}
	if(!flag)
	{
		puts("-1");
		return 0;
	}
	int min2 = 1e9, min3 = 1e9;
	for(int i = 1; i <= n; i++)
	{
		min2 = min(min2, cnt2[i]);
		min3 = min(min3, cnt3[i]);
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		res += cnt2[i] - min2;
		res += cnt3[i] - min3;
	}
	printf("%d\n", res);
	return 0;
}
