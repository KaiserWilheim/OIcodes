#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = 40;
int n;
ll a[N], b[N], d[N], f[N][M], g[N];
int sgn(ll x)
{
	if(x > 0)return 1;
	else if(x < 0)return -1;
	else return 0;
}
ll calc(ll l, ll r)
{
	vector<int>v;
	v.clear();
	if(l == r)return 1;
	if(b[l] == 0)return 1;
	for(int i = l; i <= r; i++)v.push_back(__builtin_ctzll(b[i]));
	ll sz = v.size();
	for(int i = 0; i <= sz; i++)
	{
		g[i] = 0;
		for(int j = 0; j <= 31; j++)f[i][j] = 0x3f3f3f3f;
	}
	for(int i = 0; i < sz; i++)f[i][v[i]] = i;
	for(int i = sz - 1; i >= 0; i--)
	{
		for(int j = v[i] + 1; j <= 31; j++)
		{
			if(f[i][j - 1] == 0x3f3f3f3f) { f[i][j] = 0x3f3f3f3f; continue; }
			f[i][j] = f[f[i][j - 1] + 1][j - 1];
		}
	}
	for(int i = sz - 1; i >= 0; i--)
	{
		g[i] = max(g[i], g[i + 1]);
		for(int j = 31; j > v[i]; j--)
			if(f[i][j] != 0x3f3f3f3f)
				g[i] = max(g[i], g[f[i][j] + 1] + f[i][j] - i);
	}
	return sz - g[0];
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++)
		d[i] = a[i + 1] - a[i], b[i] = abs(d[i]);
	vector<pair<int, int> >vec;
	vec.clear();
	ll pre = 1, cur = b[1] / (1ll << __builtin_ctzll(b[1]));
	for(int i = 2; i < n; i++)
	{
		bool flag = false;
		if(sgn(d[i]) != sgn(d[pre]))flag = true, vec.push_back({ pre,i - 1 });
		ll x = b[i] / (1ll << __builtin_ctzll(b[i]));
		if(!flag && x != cur)flag = true, vec.push_back({ pre,i - 1 });
		if(flag)pre = i, cur = x;
	}
	vec.push_back({ pre, n - 1 });
	ll ans = 1;
	for(auto i : vec)ans += calc(i.first, i.second);
	printf("%lld\n", ans);
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}