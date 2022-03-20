#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10010, M = 200010;
int n, m, s, t; ll ans = 0;
ll cnt = 1, first[N], nxt[M], to[M], val[M];
inline void add(int u, int v, ll w)
{
	to[++cnt] = v;
	val[cnt] = w;
	nxt[cnt] = first[u];
	first[u] = cnt;
}
int dep[N], q[N], l, r;
bool bfs()
{
	memset(dep, 0, (n + 1) * sizeof(int));

	q[l = r = 1] = s;
	dep[s] = 1;
	while(l <= r)
	{
		int u = q[l++];
		for(int p = first[u]; p; p = nxt[p])
		{
			int v = to[p];
			if(val[p] && !dep[v])
			{
				dep[v] = dep[u] + 1;
				q[++r] = v;
			}
		}
	}
	return dep[t];
}
ll dfs(int u, ll in)
{
	if(u == t)return in;
	ll out = 0;
	for(int p = first[u]; p && in; p = nxt[p])
	{
		int v = to[p];
		if(val[p] && dep[v] == dep[u] + 1)
		{
			ll res = dfs(v, min(val[p], in));
			val[p] -= res;
			val[p ^ 1] += res;
			in -= res;
			out += res;
		}
	}
	if(out == 0)dep[u] = 0;
	return out;
}
int main()
{
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for(int i = 1; i <= m; ++i)
	{
		int u, v; ll w;
		scanf("%d %d %lld", &u, &v, &w);
		add(u, v, w);
		add(v, u, 0);
	}
	while(bfs())
		ans += dfs(s, 1e18);
	printf("%lld\n", ans);
	return 0;
}
