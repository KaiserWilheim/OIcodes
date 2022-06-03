#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m, p;
int h[N], e[M], ne[M], w[M], idx;
struct edge
{
	int v, w;
};
vector<edge>v[N];
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(auto i : v[p])
	{
		int j = i.v;
		if(!dfn[j])
		{
			tarjan(j);
			low[p] = min(low[p], low[j]);
		}
		else if(vis[j])
		{
			low[p] = min(low[p], dfn[j]);
		}
	}
	if(dfn[p] == low[p])
	{
		++sc;
		while(sta[tt] != p)
		{
			scc[sta[tt]] = sc;
			sz[sc]++;
			vis[sta[tt]] = false;
			tt--;
		}
		scc[sta[tt]] = sc;
		sz[sc]++;
		vis[sta[tt]] = false;
		tt--;
	}
}
int dis[N];
queue<int>q;
void spfa(int s)
{
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[s] = 0, vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i], c = w[i];
			if(dis[v] > dis[u] + c)
			{
				dis[v] = dis[u] + c;
				if(!vis[v])
				{
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		v[a].push_back({ b,c });
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		for(auto j : v[i])
		{
			int v = j.v, w = j.w;
			if(scc[i] != scc[v])add(scc[i], scc[v], w);
		}
	}
	spfa(scc[1]);
	printf("%d\n", dis[scc[n]]);
	return 0;
}
