#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
int n, k;
int a[N];
bool vis[N];
ll x[N], y[N];
ll dis = 0;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++)
	{
		scanf("%d", &a[i]);
		vis[a[i]] = true;
	}
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &x[i], &y[i]);
	for(int i = 1; i <= n; i++)
	{
		if(vis[i])continue;
		ll res = 0x3f3f3f3f3f3f3f3f;
		for(int j = 1; j <= k; j++)
		{
			res = min(res, (x[i] - x[a[j]]) * (x[i] - x[a[j]]) + (y[i] - y[a[j]]) * (y[i] - y[a[j]]));
		}
		dis = max(dis, res);
	}
	printf("%lf\n", sqrt(dis));
	return 0;
}
