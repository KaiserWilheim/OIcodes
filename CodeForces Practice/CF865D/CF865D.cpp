#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll ans;
priority_queue<ll, vector<ll>, greater<ll> >q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		ll k;
		scanf("%lld", &k);
		if(!q.empty() && q.top() < k)
		{
			ans += k - q.top();
			q.pop();
			q.push(k);
		}
		q.push(k);
	}
	printf("%lld\n", ans);
	return 0;
}
