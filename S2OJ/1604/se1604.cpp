#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m;
ll alt[N];
int h[N], e[M], ne[M], idx;
ll w[M], f[M];
void add(int a, int b, ll c, ll d)
{
	e[idx] = b, w[idx] = c, f[idx] = d, ne[idx] = h[a], h[a] = idx++;
}
struct Node
{
	ll dis;
	int u;
	bool operator > (const Node &a)const
	{
		return dis > a.dis;
	}
};
ll dis[N];
bool vis[N];
priority_queue<Node, vector<Node>, greater<Node>>q;
void dijkstra(int s,ll lim)
{
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push({ 0,s });
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u] = true;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];ll c = w[i];
			if(dis[v] > dis[u] + c && f[i] <= lim)
			{
				dis[v] = dis[u] + c;
				if(!vis[v])q.push({ dis[v],v });
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	ll S;
	ll maxa = INT_MIN, mina = INT_MAX;
	scanf("%d%d%lld", &n, &m, &S);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &alt[i]);
		maxa = max(maxa, alt[i]);
		mina = min(mina, alt[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w, alt[v] - alt[u]);
		add(v, u, w, alt[u] - alt[v]);
	}
	ll l = mina - maxa, r = maxa - mina;
	dijkstra(1, r);
	if(dis[n] > S)
	{
		puts("NO");
		return 0;
	}
	while(l < r)
	{
		ll mid = (l + r) >> 1;
		dijkstra(1, mid);
		if(dis[n] > S)l = mid + 1;
		else r = mid;
	}
	printf("%lld\n", l);
	return 0;
}