#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
vector<pair<int, int>>cur;
bool vis[N];
pair<int, int> sta[N];
int tt;
void dfs1(int p, int fa, int id)
{
	sta[++tt] = make_pair(p, id);
	if(p == n)
	{
		for(int i = 1; i <= tt; i++)
		{
			cur.push_back(sta[i]);
			vis[sta[i].first] = true;
		}
	}
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p, i);

	}
	tt--;
}
ll dis[N], mdis[N];
int sz[N];
void dfs2(int p, int fa, int id)
{
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || vis[e[i]])continue;
		dis[e[i]] = dis[p] + w[i];
		dfs2(e[i], p, id);
		sz[p] += sz[e[i]];
	}
	mdis[id] = max(mdis[id], dis[p]);
}
bool able = false;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	dfs1(1, 0, -1);
	int k = cur.size();
	ll minn = 1e15;
	for(int i = 0; i < k; i++)
	{
		dfs2(cur[i].first, 0, cur[i].first);
		if(sz[cur[i].first] >= 3)able = true;
		if(sz[cur[i].first] > 1)
		{
			ll tmp;
			if(i == 0)tmp = w[cur[1].second] - mdis[cur[1].first];
			else if(i == k - 1)tmp = w[cur[i].second] - mdis[cur[i - 1].first];
			else tmp = min(w[cur[i].second] - mdis[cur[i - 1].first], w[cur[i + 1].second] - mdis[cur[i + 1].first]);
			tmp -= mdis[cur[i].first];
			minn = min(minn, tmp);
		}
	}
	ll tdis = 0;
	for(int i = 1; i < k; i++)
		tdis += w[cur[i].second];
	for(int i = 2; i < k; i++)
		minn = min(minn, w[cur[i].second] + w[cur[i - 1].second]);
	for(int i = 1; i <= m; i++)
	{
		ll x;
		scanf("%lld", &x);
		if(able)
		{
			printf("%lld\n", tdis);
			continue;
		}
		if(minn <= x)
		{
			printf("%lld\n", tdis);
		}
		else
		{
			printf("%lld\n", tdis - minn + x);
		}
	}
	return 0;
}
