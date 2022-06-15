#include <bits/stdc++.h>
using namespace std;
#define ll long long
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') { f = -1; } c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
const int N = 500010, M = 5000010;
int n, m;
int k;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
struct node
{
	int dis, u;
	bool operator > (const node &a) const
	{
		return dis > a.dis;
	}
};
int dis[N], vis[N];
priority_queue<node, vector<node>, greater<node> >q;
void dijkstra(int s)
{
	memset(dis, 63, sizeof(dis));
	dis[s] = 0;
	q.push({ 0,s });
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i], c = w[i];
			if(dis[v] > dis[u] + c)
			{
				dis[v] = dis[u] + c;
				if(!vis[v])q.push({ dis[v],v });
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	n = read(), m = read();
	k = read();
	int s = read(), t = read();
	for(int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read();
		add(a, b, c), add(b, a, c);
		for(int j = 1; j <= k; j++)
		{
			add(a + n * (j - 1), b + n * j, 0);
			add(b + n * (j - 1), a + n * j, 0);
			add(a + n * j, b + n * j, c);
			add(b + n * j, a + n * j, c);
		}
	}
	for(int i = 1; i <= k; i++)
		add(t + n * (i - 1), t + n * i, 0);
	dijkstra(s);
	printf("%d\n", dis[t + n * k]);
	return 0;
}
