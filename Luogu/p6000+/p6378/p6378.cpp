#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4000010, M = N << 3;
const int INF = 1e9;
int n, m, k;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
int scc[N], sc;
bool vis[N];
void tarjan(int p)
{
	dfn[p] = low[p] = ++cnt;
	sta[++tt] = p;
	vis[p] = true;
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
		sc++;
		while(sta[tt] != p)
		{
			scc[sta[tt]] = sc;
			vis[sta[tt]] = false;
			tt--;
		}
		scc[sta[tt]] = sc;
		vis[sta[tt]] = false;
		tt--;
	}
}
int neg(int x) { return x > n ? x - n : x + n; }
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(neg(a), b), add(neg(b), a);
	}
	for(int _i = 1; _i <= k; _i++)
	{
		int w;
		scanf("%d", &w);
		vector<int>e;
		for(int i = 1; i <= w; i++)
		{
			int x;
			scanf("%d", &x);
			e.push_back(x);
		}
		for(int i = 1; i < w; i++)
		{
			add(e[i - 1] + n * 2, e[i] + n * 2);
			add(neg(e[i]) + n * 2, neg(e[i - 1]) + n * 2);
			add(e[i - 1] + n * 2, neg(e[i]));
			add(e[i], neg(e[i - 1]) + n * 2);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		add(i, i + 2 * n);
		add(neg(i) + 2 * n, neg(i));
	}
	for(int i = 1; i <= n * 2; i++)
		if(!dfn[i])tarjan(i);
	bool flag = true;
	for(int i = 1; i <= n; i++)
	{
		if(scc[i] == scc[i + n])
		{
			flag = false;
			break;
		}
	}
	if(flag)puts("TAK");
	else puts("NIE");
	return 0;
}
