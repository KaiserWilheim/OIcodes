#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int a[N];
priority_queue<ll>q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n, greater<int>());
	for(int i = 0; i <= m; i++)q.push(0);
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		ll u = q.top();
		q.pop();
		ans += u;
		u += a[i];
		q.push(u);
	}
	printf("%lld\n", ans);
	return 0;
}