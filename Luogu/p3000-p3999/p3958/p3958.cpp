#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
ll n, h, r;
ll dis(ll x, ll y, ll z, ll x1, ll y1, ll z1)
{
	return (x - x1) * (x - x1) + (y - y1) * (y - y1) + (z - z1) * (z - z1);
}
ll x[N], y[N], z[N];
int p[N];
int ft[N], fb[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
void work()
{
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	memset(z, 0, sizeof(x));
	scanf("%lld%lld%lld", &n, &h, &r);
	for(int i = 1; i <= n; i++)p[i] = i;
	int tt = 0, tb = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
		if(z[i] + r >= h)ft[++tt] = i;
		if(z[i] - r <= 0)fb[++tb] = i;
		for(int j = 1; j < i; j++)
		{
			if((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) > 4 * r * r)continue;
			if(dis(x[i], y[i], z[i], x[j], y[j], z[j]) <= 4 * r * r)
			{
				int pa = find(i), pb = find(j);
				if(pa != pb)p[pa] = pb;
			}
		}
	}
	bool flag = false;
	for(int i = 1; i <= tt; i++)
	{
		for(int j = 1; j <= tb; j++)
			if(find(ft[i]) == find(fb[j]))
			{
				flag = true;
				break;
			}
		if(flag)break;
	}
	if(flag)puts("Yes");
	else puts("No");
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		work();
	}
	return 0;
}
