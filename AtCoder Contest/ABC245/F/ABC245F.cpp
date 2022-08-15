#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct node
{
	int v, nex;
}e[N * 2], ed[N * 2];

int tag[N];
int head[N], tot;
int hd[N], totd;
int n, m, a[N];
int c[N * 10];
int dfn[N * 10], low[10 * N], tim, sta[10 * N], top, cnt;
int in[N], w[N], sc[N];
bool vis[N];
void add(int x, int y)
{
	e[++tot] = { y, head[x] };
	head[x] = tot;
}
void add_c(int x, int y)
{
	ed[++totd] = { y, hd[x] };
	hd[x] = totd;
}
void tarjan(int x)
{
	dfn[x] = low[x] = ++tim;
	sta[++top] = x, vis[x] = 1;
	for(int i = head[x]; i; i = e[i].nex)
		if(!dfn[e[i].v])
		{
			tarjan(e[i].v);
			low[x] = min(low[x], low[e[i].v]);
		}
		else if(vis[e[i].v])
			low[x] = min(low[x], low[e[i].v]);
	if(low[x] == dfn[x])
	{
		cnt++;
		int y;
		do
		{
			y = sta[top--], vis[y] = 0;
			c[y] = cnt;
			w[cnt] += a[y];
			sc[cnt]++;
		} while(x != y);
	}
}
void dfs(int x)
{
	for(int i = hd[x]; i; i = ed[i].nex)
	{
		int v = ed[i].v;
		if(tag[v] == -1)
			dfs(v);
		if(tag[v] == 1 || sc[x] > 1)
			tag[x] = 1;
	}
	if(sc[x] > 1)
		tag[x] = 1;
	if(tag[x] == -1)
		tag[x] = 0;
	return;
}
signed main()
{
	memset(tag, 0xff, sizeof(tag));
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			tarjan(i);
	for(int i = 1; i <= n; i++)
	{
		for(int j = head[i]; j; j = e[j].nex)
		{
			if(c[i] == c[e[j].v])continue;
			in[c[e[j].v]]++;
			add_c(c[i], c[e[j].v]);
		}
	}
	for(int i = 1; i <= cnt; i++)
		if(!in[i])
			dfs(i);
	int ans = 0;
	for(int i = 1; i <= cnt; i++)
		if(tag[i] == 1)
			ans += sc[i];
	cout << ans << endl;
	return 0;
}
