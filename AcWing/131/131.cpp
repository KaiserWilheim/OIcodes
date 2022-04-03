#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
struct rect
{
	ll h, w;
};
rect stk[N];
int tt = 0;
ll height[N];
int main()
{
	int n;
	cin >> n;
	while(n)
	{
		for(int i = 1; i <= n; i++)
			scanf("%lld", &height[i]);
		ll ans = 0;
		for(int i = 1; i <= n + 1; i++)
		{
			ll width = 0;
			while(tt && stk[tt].h >= height[i])
			{
				ans = max(ans, (width + stk[tt].w) * stk[tt].h);
				width += stk[tt--].w;
			}
			stk[++tt] = { height[i],width + 1 };
		}
		cout << ans << endl;
		for(int i = 1; i <= n; i++)height[i] = 0;
		cin >> n;
	}
	return 0;
}
