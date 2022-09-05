#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int N = 1000010, M = 4000010;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
struct node
{
	int dis, u;
	bool operator > (const node &a) const
	{
		return dis > a.dis;
	}
};
int dis[N], vis[N];
priority_queue<node, vector<node>, greater<node> >q;
void dijkstra(int s)
{
	memset(dis, 63, sizeof(dis));
	dis[s] = 0;
	q.push({ 0,s });
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i], c = w[i];
			if(dis[v] > dis[u] + c)
			{
				dis[v] = dis[u] + c;
				if(!vis[v])q.push({ dis[v],v });
			}
		}
	}
}
vector<int>vec[N];
map<pair<int, int>, int>dic;
int cnt;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	cnt = n;
	for(int i = 1; i <= m; i++)
	{
		int u, v, p;
		scanf("%d%d%d", &u, &v, &p);
		if(!dic.count(make_pair(u, p)))
		{
			dic.insert(make_pair(make_pair(u, p), ++cnt));
			vec[u].push_back(cnt);
		}
		if(!dic.count(make_pair(v, p)))
		{
			dic.insert(make_pair(make_pair(v, p), ++cnt));
			vec[v].push_back(cnt);
		}
		int uu = dic.find(make_pair(u, p))->second;
		int vv = dic.find(make_pair(v, p))->second;
		add(uu, vv, 0), add(vv, uu, 0);
	}
	for(int i = 1; i <= n; i++)
	{
		if(vec[i].empty())continue;
		for(int u : vec[i])
			add(i, u, 1), add(u, i, 0);
	}
	dijkstra(1);
	if(dis[n] == 0x3f3f3f3f)puts("-1");
	else printf("%d\n", dis[n]);
	return 0;
}