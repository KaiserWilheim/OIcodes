#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll ans;
struct Biru
{
	ll t, a;
	bool operator < (const Biru &x)const
	{
		return t < x.t;
	}
}w[200010];
priority_queue<ll, vector<ll> >q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &w[i].a, &w[i].t);
	sort(w + 1, w + 1 + n);
	ll now = 0;
	for(int i = 1; i <= n; i++)
	{
		if(now + w[i].a > w[i].t)
		{
			if(w[i].a < q.top())
			{
				now += w[i].a - q.top();
				q.pop();
				q.push(w[i].a);
			}
		}
		else
		{
			q.push(w[i].a);
			ans++;
			now += w[i].a;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
