#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010, M = 410, INF = 2000000000;
ll dis[M], val[N], a[20], maxn = -1, minn = M;
int q[N], used[M], n, point[N], yest[N], last[M], total;
void add(int f, int t, int v)
{
	point[++total] = t;
	val[total] = v;
	yest[total] = last[f];
	last[f] = total;
}
void spfa(int p)
{
	memset(dis, -1, sizeof(dis));
	dis[p] = 0;
	used[p] = 1;
	int hh = 1, tt = 1;
	q[1] = p;
	int f, t;
	while(hh <= tt)
	{
		f = q[hh];
		for(int i = last[f]; i; i = yest[i])
		{
			t = point[i];
			if((dis[t] == -1) || (dis[f] + val[i] < dis[t]))
			{
				dis[t] = dis[f] + val[i];
				if(!used[t])
				{
					used[t] = 1;
					q[++tt] = t;
				}
			}
		}
		used[f] = 0;
		hh++;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		minn = min(minn, a[i]);
	}
	for(int i = 0; i < minn; i++)
		for(int j = 1; j <= n; j++)
			add(i, (i + a[j]) % minn, a[j]);
	spfa(0);
	int flag = 1;
	for(int i = 0; i < minn; i++)
	{
		if((dis[i] == -1) || (dis[i] - minn > INF))
		{
			flag = 0;
			break;
		}
		else
		{
			maxn = max(maxn, dis[i]);
		}
	}
	if(!flag) puts("0");
	else
	{
		if(maxn - minn >= 0) printf("%lld\n", maxn - minn);
		else puts("0");
	}
	return 0;
}
