#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
ll kpd(ll a, ll b)
{
	return b ? kpd(b, a % b) : a;
}
#define chq(a,b) (((a)%g==0)&&((b)%g==0))
void solve()
{
	ll a, b, x, y;
	scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
	ll g = kpd(a, b) * 2;
	if(chq(x, y))puts("Y");
	else if(chq(x + a, y + b))puts("Y");
	else if(chq(x + b, y + a))puts("Y");
	else if(chq(x + a + b, y + a + b))puts("Y");
	else puts("N");
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