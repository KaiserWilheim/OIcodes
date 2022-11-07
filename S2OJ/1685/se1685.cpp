#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
ll ceil(ll a, ll b)
{
	if(a % b == 0)return a / b;
	else return a / b + 1;
}
ll ret(ll a, ll b)
{
	if(a % b == 0)return b;
	else return a - a / b * b;
}
ll n, m, a, b;
void solve()
{
	scanf("%lld%lld%lld%lld", &n, &m, &a, &b);
	ll x = n * b, y = m * a;
	while(x > 0 && y > 0)
	{
		ll dx = ceil(y, a);
		ll dy = ceil(x, b);
		ll k = min(ceil(ret(x, b), dx), ceil(ret(y, a), dy));
		x -= k * dx, y -= k * dy;
	}
	if(x <= 0)cout << 0 << endl;
	else cout << ceil(x, b) << endl;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}