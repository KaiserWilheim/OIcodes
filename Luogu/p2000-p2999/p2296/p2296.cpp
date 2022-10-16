#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 500010;
int n, m;
int h[N], hs[N], e[M], ne[M], idx;
void add(int a, int b, int *h)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool vis[N];
bool cfr[N], cps[N];
int dis[N];
void bfs(int s, int *h)
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	queue<int>q;
	dis[s] = 0;
	vis[s] = true;
	q.push(s);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(!cps[e[i]])continue;
			dis[e[i]] = min(dis[e[i]], dis[p] + 1);
			if(vis[e[i]])continue;
			q.push(e[i]);
			vis[e[i]] = true;
			dis[e[i]] = dis[p] + 1;
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	memset(hs, -1, sizeof(hs));
	memset(cps, true, sizeof(cps));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v, h), add(v, u, hs);
	}
	int s, t;
	scanf("%d%d", &s, &t);
	bfs(t, hs);
	for(int i = 1; i <= n; i++)
		if(vis[i])cfr[i] = true;
	for(int i = 1; i <= n; i++)
	{
		bool flag = true;
		for(int j = h[i]; ~j; j = ne[j])
		{
			if(!cfr[e[j]])
			{
				flag = false;
				break;
			}
		}
		cps[i] = flag;
	}
	if(!cps[s])
	{
		puts("-1");
		return 0;
	}
	bfs(s, h);
	if(!vis[t])puts("-1");
	else printf("%d\n", dis[t]);
	return 0;
}