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
struct wed
{
	int s, t, d;
}w[N];
bool colli(int a, int b, int c, int d)
{
	return d > a && b > c;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int sa, ss, ta, tt, d;
		scanf("%d:%d %d:%d %d", &sa, &ss, &ta, &tt, &d);
		w[i].s = sa * 60 + ss;
		w[i].t = ta * 60 + tt;
		w[i].d = d;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			auto a = w[i], b = w[j];
			if(colli(a.s, a.s + a.d, b.s, b.s + b.d))add(i, j + n), add(j, i + n);
			if(colli(a.s, a.s + a.d, b.t - b.d, b.t))add(i, j), add(j + n, i + n);
			if(colli(a.t - a.d, a.t, b.s, b.s + b.d))add(i + n, j + n), add(j, i);
			if(colli(a.t - a.d, a.t, b.t - b.d, b.t))add(i + n, j), add(j + n, i);
		}
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i])tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		if(scc[i] == scc[i + n])
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	for(int i = 1; i <= n; i++)
	{
		auto a = w[i];
		if(scc[i] < scc[i + n])
			printf("%02d:%02d %02d:%02d\n", a.s / 60, a.s % 60, (a.s + a.d) / 60, (a.s + a.d) % 60);
		else
			printf("%02d:%02d %02d:%02d\n", (a.t - a.d) / 60, (a.t - a.d) % 60, a.t / 60, a.t % 60);
	}
	return 0;
}
