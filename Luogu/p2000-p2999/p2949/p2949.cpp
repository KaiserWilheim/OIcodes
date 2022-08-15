#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll ans;
struct Item
{
	ll t, v;
	bool operator < (const Item &a)const
	{
		return t < a.t;
	}
}w[100010];
priority_queue<ll, vector<ll>, greater<ll> >q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &w[i].t, &w[i].v);
	sort(w + 1, w + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		if(w[i].t <= q.size())
		{
			if(w[i].v > q.top())
			{
				ans += w[i].v - q.top();
				q.pop();
				q.push(w[i].v);
			}
		}
		else
		{
			q.push(w[i].v);
			ans += w[i].v;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
