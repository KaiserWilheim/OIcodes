#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
const ll INF = 0x8080808080808080;
int n, d;
ll k;
int dis[N], a[N];
ll f[N];
bool chq(int g)
{
	int l = max(1, d - g), r = d + g;
	memset(f, 128, sizeof(f));
	f[0] = 0;
	deque<int>q;
	int pre = 0;
	for(int i = 1; i <= n; i++)
	{
		while(dis[i] - dis[pre] >= l && pre < i)
		{
			if(f[pre] != INF)
			{
				while(!q.empty() && f[q.back()] < f[pre])q.pop_back();
				q.push_back(pre);
			}
			pre++;
		}
		while(!q.empty() && dis[i] - dis[q.front()] > r)q.pop_front();
		if(!q.empty())f[i] = f[q.front()] + a[i];
	}
	ll res = INF;
	for(int i = 1; i <= n; i++)
		res = max(res, f[i]);
	return res >= k;
}
int main()
{
	scanf("%d%d%lld", &n, &d, &k);
	ll tot = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &dis[i], &a[i]);
		if(a[i] > 0)tot += a[i];
	}
	if(tot < k)
	{
		puts("-1");
		return 0;
	}
	int l = 0, r = max(dis[n], d);
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(chq(mid))r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}