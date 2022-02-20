#include<bits/stdc++.h>
using namespace std;
const int N = 51;
#define ll long long
int n;
ll ans;
ll a[N], p[N << 1];
void getlb(ll x)
{
	for(int i = 62; i >= 0; i--)
	{
		if(!(x >> ( long long )i))continue;
		if(!p[i])
		{
			p[i] = x;
			break;
		}
		x ^= p[i];
	}
	return;
}
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		getlb(a[i]);
	}
	for(int i = 62; i >= 0; i--)
	{
		ans = max(ans, ans ^ p[i]);
	}
	cout << ans << endl;
	return 0;
}
