#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
ll a[N];
priority_queue<ll>q;
int main()
{
	scanf("%d", &n);
	ll sum = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		if(a[i] > 0)sum += a[i];
		else q.push(a[i]);
	}
	m = q.size();
	ll sum1 = 0, sum2 = 0;
	while(!q.empty())
	{
		sum1 += q.top();
		q.pop();
		if(!q.empty())
		{
			sum2 += q.top();
			q.pop();
		}
	}
	if(sum == 0)printf("%lld\n", max(sum1, a[1] + sum2));
	else printf("%lld\n", sum + max(sum1, sum2));
	return 0;
}