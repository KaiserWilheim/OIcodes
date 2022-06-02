#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
int n, m, p;
vector<int>v[N];
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
int w[N], sum[N];
int deg[N], top[N], tot;
int dis[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(auto j : v[p])
	{
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
			sum[sc] += w[sta[tt]];
			tt--;
		}
		scc[sta[tt]] = sc;
		sz[sc]++;
		vis[sta[tt]] = false;
		sum[sc] += w[sta[tt]];
		tt--;
	}
}
void topsort()
{
	queue<int>q;
	for(int i = 1; i <= n; i++)
	{
		if(deg[i] == 0)
		{
			q.push(i);
			top[++tot] = i;
			dis[i] = sum[i];
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			dis[v] = max(dis[v], dis[u] + sum[v]);
			deg[v]--;
			if(deg[v] == 0)
			{
				q.push(v);
				top[++tot] = v;
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		v[a].push_back(b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
		for(auto j : v[i])
			if(scc[i] != scc[j])
				add(scc[i], scc[j]), deg[scc[j]]++;
	topsort();
	int maxn = 0;
	for(int i = 1; i <= sc; i++)
		maxn = max(maxn, dis[i]);
	printf("%d\n", maxn);
	return 0;
}
