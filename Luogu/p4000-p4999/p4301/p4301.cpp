#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, m;
int a[N];
int d[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n, greater<int>());
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int x = a[i];
		for(int j = 30; j >= 0; j--)
		{
			if((x >> j) & 1)
			{
				if(d[j])x ^= d[j];
				else
				{
					d[j] = x;
					break;
				}
			}
		}
		if(!x)ans += a[i];
	}
	printf("%lld\n", ans);
	return 0;
}