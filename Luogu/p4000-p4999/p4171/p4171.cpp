#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, M = 4000010;
int n, m;
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
void solve()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		string s1, s2;
		cin >> s1 >> s2;
		int u = 0, v = 0, a, b;
		if(s1[0] == 'm')a = 0;
		else a = 1;
		if(s2[0] == 'm')b = 0;
		else b = 1;
		int k;
		k = 1;
		while(isdigit(s1[k]))u = u * 10 + s1[k++] - 48;
		k = 1;
		while(isdigit(s2[k]))v = v * 10 + s2[k++] - 48;
		add(u + !a * n, v + b * n);
		add(v + !b * n, u + a * n);
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		if(scc[i] == scc[i + n])
		{
			puts("BAD");
			return;
		}
	}
	puts("GOOD");
	return;
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		memset(h, -1, sizeof(h));
		memset(dfn, 0, sizeof(dfn));
		idx = 0;
		solve();
	}
	return 0;
}
