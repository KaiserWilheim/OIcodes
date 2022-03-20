#include<bits/stdc++.h>
const int N = 1000010;
using namespace std;
int sum[N], c[N];
int n, m, k;
int a[N], b[N];
int vis[N];

int main()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++)
	{
		cin >> b[i];
		vis[b[i]] = 1;
	}
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] %= k;
		sum[i] = sum[i - 1] + a[i];
		sum[i] %= k;
	}
	for(int i = 1; i <= m; i++)
		c[sum[b[i]]]++;
	int now = 0, ans = c[0];
	for(int i = 1; i <= n; i++)
	{
		if(vis[i])
			c[sum[i]]--;
		ans = max(ans, now + c[a[i]]);
		if(!sum[i] && vis[i])
			now++;
		ans = max(ans, now);
	}
	cout << ans << endl;
	return 0;
}
