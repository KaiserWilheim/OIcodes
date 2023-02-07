#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 40010, M = 80010;
const int INF = 1e9;
int n1, n2, m;
int S, T;
int h[N], e[M], ne[M], f[M], idx;
int id[N];
void add(int a, int b, int c, int d)
{
	e[idx] = b, ne[idx] = h[a], f[idx] = c, id[idx] = d, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, id[idx] = d, h[b] = idx++;
}
int d[N];
bool bfs()
{
	queue<int>q;
	memset(d, -1, sizeof(d));
	q.push(S), d[S] = 0;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				if(v == T)return true;
				q.push(v);
			}
		}
	}
	return false;
}
int find(int u, int lim)
{
	if(u == T)return lim;
	int flow = 0;
	for(int i = h[u]; ~i && flow <= lim; i = ne[i])
	{
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], lim - flow));
			if(!t)d[v] = -1;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	return flow;
}
int dinic()
{
	int res = 0, flow;
	while(bfs())while(flow = find(S, INF))res += flow;
	return res;
}
int deg[N];
vector<int>ans[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n1, &n2, &m);
	S = 0, T = n1 + n2 + 1;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		v += n1;
		add(u, v, 1, i);
		deg[u]++, deg[v]++;
	}
	int mindeg = 1e9;
	for(int i = 1; i <= n1 + n2; i++)
		mindeg = min(mindeg, deg[i]);
	for(int i = 1; i <= n1; i++)
		add(S, i, deg[i] - mindeg, 0);
	for(int i = 1; i <= n2; i++)
		add(i + n1, T, deg[i + n1] - mindeg, 0);
	for(int k = mindeg; k > 0; k--)
	{
		dinic();
		for(int i = 1; i <= n1; i++)
		{
			for(int j = h[i]; ~j; j = ne[j])
				if(f[j] && id[j])ans[k].push_back(id[j]);
		}
		for(int i = h[S]; ~i; i = ne[i])f[i]++;
		for(int i = h[T]; ~i; i = ne[i])f[i ^ 1]++;
	}
	for(int k = 0; k <= mindeg; k++)
	{
		printf("%d ", ans[k].size());
		for(auto i : ans[k])
			printf("%d ", i);
		putchar('\n');
	}
	return 0;
}
