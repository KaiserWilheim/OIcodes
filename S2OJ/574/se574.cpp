#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
const ll mod = 1e9 + 7;
const ll base = 131;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
int n;
string s;
ll ph[N], sh[N];
vector<int>ans;
void chq(int l, int r)
{
	if(r < 3)return;
	int mid = (l + r) >> 1;
	int len = r - mid;
	ll prf = ph[mid - 1];
	ll suf = (sh[mid + 1] - sh[r + 1] * qpow(base, len) % mod + mod) % mod;
	if(prf == suf)
	{
		ans.push_back(mid);
		chq(1, mid);
	}
}
void solve()
{
	ans.clear();
	cin >> s;
	n = s.length();
	ph[0] = 0, sh[n + 1] = 0;
	for(int i = 1; i <= n; i++)
		ph[i] = (ph[i - 1] * base + s[i - 1] - '`') % mod;
	for(int i = n; i >= 1; i--)
		sh[i] = (sh[i + 1] * base + s[i - 1] - '`') % mod;
	for(int i = n - 1; i >= n / 2 + 1; i--)
	{
		int len = n - i;
		ll suf = sh[i + 1];
		ll prf = (ph[i - 1] - ph[i - 1 - len] * qpow(base, len) % mod + mod) % mod;
		if(suf == prf)
		{
			ans.push_back(i);
			chq(1, i);
		}
	}
	sort(ans.begin(), ans.end());
	ans.push_back(n);
	for(int i = 1; i < ans.size(); i++)
		printf("%d ", ans[i - 1]);
	printf("%d", ans[ans.size() - 1]);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
		if(T > 0)putchar('\n');
	}
	return 0;
}