#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) ((x)&-(x))
const int N = 100010, M = N << 1;
const ll mod = 1e9 + 7, inv2 = 500000004;
int n, m;
int a[N], b[N];
int cnt[N];
ll C2(ll x)
{
	return inv2 * x * (x - 1) % mod;
}
ll ans;
struct Bit
{
	ll tr[N];
	void segadd(int x, ll c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr[i] = (tr[i] + c) % mod;
	}
	ll segsum(int x)
	{
		ll res = 0;
		for(int i = x; i; i -= lowbit(i))
			res = (res + tr[i]) % mod;
		return res;
	}
};
Bit bit;
vector<int>g[N], op[N];
ll t[N];
void solve()
{
	int len = 40;
	for(int i = 1; i <= n; i++)g[a[i]].push_back(i);
	for(int x = 1; x <= m; x++)
	{
		if(g[x].size() < len)continue;
		for(int i = 1; i <= n; i++)
			t[i] = t[i - 1] + (a[i] == x);
		for(int y = 1; y <= m; y++)
		{
			if(x == y)continue;
			int pre = 0;
			for(auto i : g[y])
			{
				ans = (ans - (pre * (t[n] - t[i]) % mod) + mod) % mod;
				pre = (pre + t[i - 1]) % mod;
			}
			if(g[y].size() >= len)continue;
			ll s0 = 0, s1 = 0, s2 = 0;
			for(auto i : g[y])
			{
				s0++;
				s1 = (s1 + t[i]) % mod;
				s2 = (s2 + (t[i] * t[i] % mod)) % mod;
			}
			for(auto i : g[y])
			{
				s0--;
				s1 = (s1 - t[i] + mod) % mod;
				s2 = (s2 - (t[i] * t[i] % mod) + mod) % mod;
				ll tmp = (s2 - s1 + t[i] * s0 % mod + t[i] * t[i] % mod * s0 % mod - 2 * t[i] * s1 % mod) % mod;
				tmp = ((tmp + mod) * inv2) % mod;
				ans = (ans - tmp + mod) % mod;
			}
		}
	}
	for(int x = 1; x <= m; x++)
	{
		if(g[x].size() >= len)continue;
		for(int i=0;i<g[x].size();i++)
		{
			for(int j = i + 1; j < g[x].size(); j++)
			{
				op[g[x][i]].push_back(g[x][j]);
				ans = (ans + C2(j - i - 1)) % mod;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(auto x : op[i])
			ans = (ans - (bit.segsum(n) - bit.segsum(x) + mod) % mod + mod) % mod;
		for(auto x : op[i])
			bit.segadd(x, 1);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		cnt[a[i]]++;
		b[i] = a[i];
	}
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
	ll last = 0;
	for(int i = 1; i <= m; i++)
		last = (last + C2(cnt[i])) % mod;
	for(int i = 1; i <= m; i++)
	{
		last = (last - C2(cnt[i]) + mod) % mod;
		ans = (ans + C2(cnt[i]) * last % mod) % mod;
	}
	ll pre = 0;
	for(int i = 1; i <= n; i++)
	{
		ans = (ans - ((cnt[a[i]] - t[a[i]] - 1) * ((pre - C2(t[a[i]]) + mod) % mod) % mod) + mod) % mod;
		pre = (pre + (mod - C2(t[a[i]]) + C2(t[a[i]] + 1))) % mod;
		t[a[i]]++;
	}
	solve();
	printf("%lld\n", ans);
	return 0;
}