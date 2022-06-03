#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
const int mod = 1e9 + 7;
int n, m, p;
int h[N], e[M], ne[M], idx;
int w[N];
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int p)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p, vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
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
int minn[N], cntn[N];
int main()
{
	memset(h, -1, sizeof(h));
	memset(minn, 63, sizeof(minn));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		if(minn[scc[i]] == w[i])cntn[scc[i]]++;
		else if(minn[scc[i]] > w[i])minn[scc[i]] = w[i], cntn[scc[i]] = 1;
	}
	int ans = 0, res = 1;
	for(int i = 1; i <= sc; i++)
		ans += minn[i], res = (res * cntn[i]) % mod;
	printf("%d %d\n", ans, res);
	return 0;
}
