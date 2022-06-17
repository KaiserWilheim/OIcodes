#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = 500010;
int n, m;
int k;
int f[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
bool vis[N];
int scc[N], sc, sz[N];
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
map<string, int>dic;
int tot = 0;
pair<int, int>mar[N];
int main()
{
	memset(h, -1, sizeof(h));
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string a, b;
		cin >> a >> b;
		dic.insert(make_pair(a, ++tot));
		dic.insert(make_pair(b, ++tot));
		mar[i] = make_pair(tot - 1, tot);
		add(tot - 1, tot);
	}
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		string a, b;
		cin >> a >> b;
		int u = dic[a], v = dic[b];
		add(v, u);
	}
	for(int i = 1; i <= tot; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		if(scc[mar[i].first] == scc[mar[i].second])puts("Unsafe");
		else puts("Safe");
	}
	return 0;
}
