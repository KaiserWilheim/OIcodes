#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll,int> 
#define mp make_pair
const int N = 100010, M = 300010;
const ll INF = 1e18;
int n, q, T;
struct edge
{
	int u, v, z;
}e[M];
vector<pair<int, int>> g[N];
ll dis[N];
bool vis[N];
vector<int> st;
ll dijkstra(int s, int t)
{
	priority_queue<pli, vector<pli>, greater<pli>> que;
	vector<int> p;
	dis[s] = 0, que.push(mp(dis[s], s));
	while(que.size())
	{
		int u = que.top().second; que.pop();
		if(vis[u]) continue;
		vis[u] = true, p.emplace_back(u);
		for(auto x : g[u])
		{
			int v = x.first, len = x.second;
			if(dis[u] + len < dis[v])
			{
				dis[v] = dis[u] + len;
				que.push(mp(dis[v], v));
			}
		}
	}
	ll res = dis[t];
	for(auto v : p)
		dis[v] = INF, vis[v] = 0, g[v].clear();
	for(auto v : st)
		g[v].clear();
	return res;
}
void add(int u, int v, int w)
{
	g[u].emplace_back(v, w);
}
bool check(int L, int R)
{
	st.clear();
	for(int i = L; i <= min(R, q); ++i)
	{
		add(e[i].u, e[i].v, e[i].z), add(e[i].v, e[i].u, e[i].z);
		st.push_back(e[i].u), st.push_back(e[i].v);
	}
	if(dijkstra(1, n) <= T) return true;
	return false;
}
int main(void)
{
	scanf("%d%d%d", &n, &q, &T);
	for(int i = 1; i <= q; ++i)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].z);
	vector<int> ans;
	memset(dis, 0x3f, sizeof(dis));
	int pos = 0;
	while(pos < q)
	{
		int m = -1, lst = pos;
		if(check(pos + 1, pos + 1))
		{
			pos++;
			ans.push_back(pos);
			continue;
		}
		for(int j = 0; j <= 19; ++j)
		{
			if(check(pos + 1, pos + (1 << j)))
			{
				m = j - 1;
				break;
			}
		}
		if(m == -1) break;
		for(int j = m; j >= 0; --j)
		{
			if(!check(pos + 1, lst + (1 << j)))
			{
				lst += (1 << j);
			}
		}
		pos = lst + 1;
		ans.push_back(pos);
	}
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d ", i);
	putchar('\n');
	return 0;
}