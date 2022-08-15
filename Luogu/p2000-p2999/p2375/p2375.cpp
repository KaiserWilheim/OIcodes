#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
void solve()
{
	string s;
	cin >> s;
	ll n = (ll)s.length();
	vector<ll>ne(n + 1), num(n + 1);
	ll j = 0;
	num[1] = 1;
	for (ll i = 1; i < n; i++)
	{
		while (j > 0 && s[i] != s[j])j = ne[j];
		if (s[i] == s[j])j++;
		ne[i + 1] = j;
		num[i + 1] = num[j] + 1;
	}
	ll ans = 1;
	j = 0;
	for (int i = 1; i < n; i++)
	{
		while (j > 0 && s[i] != s[j])j = ne[j];
		if (s[i] == s[j])j++;
		while (j * 2 > (i + 1))j = ne[j];
		ans = (ans * (num[j] + 1)) % mod;
	}
	cout << ans << endl;
	return;
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
	{
		solve();
	}
	return 0;
}