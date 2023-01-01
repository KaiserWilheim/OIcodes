#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
unordered_map<int, ll>dic;
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ll f[N];
void dfs(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		f[e[i]] = f[p] ^ w[i];
		dfs(e[i], p);
	}
}
mt19937_64 rnd(time(0) * 19260817ll);
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		h[i] = -1;
	for(int i = 1; i < n; i++)
	{
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		if(!dic.count(w))dic[w] = rnd() + 1;
		w = dic[w];
		add(u, v, w), add(v, u, w);
	}
	f[1] = 0;
	dfs(1, 0);
	ll ans = 1ll * n * (n - 1) / 2;
	map<ll, ll>cnt;
	for(int i = 1; i <= n; i++)
		cnt[f[i]]++;
	for(auto i : cnt)
		ans -= i.second * (i.second - 1) / 2;
	printf("%lld\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = 0;
		solve();
	}
	return 0;
}