#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dis[N], tot[N];
bool vis[N];
void add(int a, int b, int c)
{
	e[++idx] = b;
	ne[idx] = h[a];
	h[a] = idx;
	w[idx] = c;
}
bool spfa(int s)
{
	queue<int> q;
	memset(dis, 63, sizeof(dis));
	memset(vis, false , sizeof(vis));
	memset(tot, 0, sizeof(tot));
	dis[s] = 0, vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = h[u]; i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				if(!vis[v])
				{
					vis[v] = 1, tot[v]++;
					if(tot[v] == n + 1)return false;
					q.push(v);
				}
			}
		}
	}
	return true;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(h, -1, sizeof(h));
		idx = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add(u, v, w);
			if(w >= 0)add(v, u, w);
		}
		if(spfa(1))puts("NO");
		else puts("YES");
	}
	return 0;
}
