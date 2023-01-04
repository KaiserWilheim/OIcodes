#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 400010;
ll len, num[12];
ll f[12][12][12][2][2][2][2];
ll dp(int p, int pre, int ppre, bool same, bool lim, bool vier, bool acht)
{
	if(vier && acht)return 0;
	if(p <= 0)return same;
	if(~f[p][pre][ppre][same][lim][vier][acht])return f[p][pre][ppre][same][lim][vier][acht];
	ll res = 0, sum = (!lim) ? num[p] : 9;
	for(int i = 0; i <= sum; i++)
		res += dp(p - 1, i, pre, same || (i == pre && i == ppre), lim || (i < sum), vier || (i == 4), acht || (i == 8));
	f[p][pre][ppre][same][lim][vier][acht] = res;
	return res;
}
ll calc(ll x)
{
	if(x < 1e10)return 0ll;
	memset(f, -1, sizeof(f));
	len = 0;
	while(x)
	{
		num[++len] = x % 10;
		x /= 10;
	}
	ll res = 0;
	for(ll i = 1; i <= num[len]; i++)
		res += dp(10, i, 0, 0, i < num[len], i == 4, i == 8);
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