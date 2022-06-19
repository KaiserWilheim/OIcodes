#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 200010;
int n, m;
int h[N], e[M], ne[M], idx;
int isBridge[M];
int dfn[N], low[N], cnt;
int sta[N], tt;
int scc[N], sc, sz[N];
int deg[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int p, int from)
{
	low[p] = dfn[p] = ++cnt;
	sta[++tt] = p;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j, i);
			low[p] = min(low[p], low[j]);
			if(dfn[p] < low[j])
				isBridge[i] = isBridge[i ^ 1] = true;
		}
		else if(i != (from ^ 1))
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
			tt--;
		}
		scc[sta[tt]] = sc;
		sz[sc]++;
		tt--;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	tarjan(1, -1);
	for(int i = 0; i < idx; i++)
		if(isBridge[i])
			deg[scc[e[i]]]++;
	int cnt = 0;
	for(int i = 1; i <= sc; i++)
		if(deg[i] == 1)cnt++;
	printf("%d\n", (cnt + 1) / 2);
	return 0;
}
