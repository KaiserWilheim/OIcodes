#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll mod = 1e9 + 7;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool vis[N], cur[N], tag[N];
int sta[N], tt;
int fa[N];
ll b[N];
ll f(ll x)
{
	return (x * x % mod * x % mod + 17) % mod;
}
void dfs(int p, int fa)
{
	vis[p] = cur[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		if(!vis[e[i]])
		{
			::fa[e[i]] = p;
			dfs(e[i], p);
		}
		else if(cur[e[i]])
		{
			for(int j = p; j != e[i]; j = ::fa[j])
				sta[++tt] = j;
			sta[++tt] = e[i];
		}
	}
	cur[p] = false;
}
ll geth(int p, int fa)
{
	ll res = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || tag[e[i]])continue;
		res = (res + f(geth(e[i], p))) % mod;
	}
	return res;
}
void solve()
{
	idx = 0, tt = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		h[i] = -1;
		vis[i] = tag[i] = false;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	if(m == n - 1)
	{
		puts("YES");
		return;
	}
	else if(m > n)
	{
		puts("NO");
		return;
	}
	dfs(1, 0);
	for(int i = 1; i <= tt; i++)
		tag[sta[i]] = true;
	for(int i = 1; i <= tt; i++)
		b[i] = geth(sta[i], 0);
	bool flag = true;
	for(int i = 1; i < tt; i++)
		flag &= (b[i] == b[i + 1]);
	if(flag)
	{
		puts("YES");
		return;
	}
	if(tt % 2 == 0)
	{
		flag = true;
		for(int i = 1; i + 2 <= tt; i++)
			flag &= (b[i] == b[i + 2]);
		if(flag)
		{
			puts("YES");
			return;
		}
	}
	puts("NO");
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
