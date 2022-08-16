#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
struct cow
{
	ll x;
	int type;
	bool operator < (const cow &a)const
	{
		return x < a.x;
	}
}a[N];
int sum[N];
map<int, int>pos;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		ll x;
		string s;
		cin >> x >> s;
		a[i].x = x;
		a[i].type = (s == "W") ? 1 : -1;
	}
	sort(a + 1, a + 1 + n);
	ll ans = 0;
	pos[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + a[i].type;
		if(sum[i] < 0)
		{
			if(!pos[sum[i]])pos[sum[i]] = i;
			else ans = max(ans, a[i].x - a[pos[sum[i]] + 1].x);
		}
		else
		{
			if(sum[i] % 2 == 0)ans = max(ans, a[i].x - a[1].x);
			else ans = max(ans, a[i].x - a[2].x);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
