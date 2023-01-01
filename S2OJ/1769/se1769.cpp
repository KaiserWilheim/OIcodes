#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll mod = 1e9 + 7;
int n;
ll a[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll zwei[N];
ll ans;
void add(int x, int *cnt)
{
	for(int i = 0; i < 30; i++)
	{
		if(x & 1)cnt[i]++;
		x >>= 1;
	}
}
void dfs(int p)
{
	int cnt[31];
	memset(cnt, 0, sizeof(cnt));
	int tot = 1;
	add(a[p], cnt);
	for(int i = h[p]; ~i; i = ne[i])
	{
		dfs(e[i]);
		add(a[e[i]], cnt);
		tot++;
	}
	if(tot == 1)return;
	ll tmp;
	ll odd = zwei[tot - 1], even = zwei[n - tot];
	if(p == 1)odd = zwei[tot - 2];
	if(p != 1)even = zwei[n - tot - 1];
	for(int i = 0; i < 30; i++)
	{
		if(cnt[i])
		{
			tmp = (1ll << i);
			ll x = odd;
			if(p == 1 && ((a[p] >> i) & 1) && (cnt[i] == 1))x = x * 2 % mod;
			ans = (ans + tmp * x % mod * even % mod) % mod;
		}
	}
	ans = ((ans - a[p] * even % mod) % mod + mod) % mod;
	if(p != 1)
	{
		for(int i = h[p]; ~i; i = ne[i])
			ans = ((ans - a[e[i]] * even % mod) % mod + mod) % mod;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 2; i <= n; i++)
	{
		int fa;
		scanf("%d", &fa);
		add(fa, i);
	}
	zwei[0] = 1;
	for(int i = 1; i <= 1e5; i++)
		zwei[i] = zwei[i - 1] * 2 % mod;
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}