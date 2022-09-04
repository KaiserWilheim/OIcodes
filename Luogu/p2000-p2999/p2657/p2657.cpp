#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 400010;
ll len, num[12];
ll f[12][12];
ll dp(int p, int pre, bool pfx, bool lim)
{
	if(p == 0)return 1;
	if(!lim && ~f[p][pre])return f[p][pre];
	ll res = 0, sum = lim ? num[p] : 9;
	for(int i = 0; i <= sum; i++)
	{
		if(abs(i - pre) < 2)continue;
		if(pfx && i == 0)res += dp(p - 1, -2, 1, lim && (i == sum));
		else res += dp(p - 1, i, 0, lim && (i == sum));
	}
	if(!lim && !pfx)f[p][pre] = res;
	return res;
}
ll calc(ll x)
{
	memset(f, -1, sizeof(f));
	len = 0;
	while(x)
	{
		num[++len] = x % 10;
		x /= 10;
	}
	ll res = dp(len, -2, 1, 1);
	return res;
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll l, r;
	cin >> l >> r;
	cout << calc(r) - calc(l - 1) << endl;
	return 0;
}