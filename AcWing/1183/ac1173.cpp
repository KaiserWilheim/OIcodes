#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 200010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], tot;
int rt, ans;
void tarjan(int p)
{
	dfn[p] = low[p] = ++tot;
	int cnt = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j);
			low[p] = min(low[p], low[j]);
			if(low[j] >= dfn[p])cnt++;
		}
		else low[p] = min(low[p], dfn[j]);
	}
	if(p != rt)cnt++;
	ans = max(ans, cnt);
}
void solve()
{
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	ans = 0;
	int cnt = 0;
	for(rt = 0; rt < n; rt++)
	{
		if(!dfn[rt])
		{
			cnt++;
			tarjan(rt);
		}
	}
	printf("%d\n", ans + cnt - 1);
}
int main()
{
	while(scanf("%d%d", &n, &m), m || n)
	{
		memset(dfn, 0, sizeof(dfn));
		memset(h, -1, sizeof(h));
		idx = 0;
		tot = 0;
		solve();
	}
	return 0;
}
