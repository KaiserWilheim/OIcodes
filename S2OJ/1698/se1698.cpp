#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 2000010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c - 48), c = getchar();
	return x;
}
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
}
bool schw[N], weis[N], full[N];
bool vis[N];
void bfs(int s)
{
	queue<int>q;
	weis[s] = true;
	vis[s] = true;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; i; i = ne[i])
		{
			int v = e[i];
			if(schw[u])weis[v] = true;
			if(weis[u])schw[v] = true;
			if(!vis[v])
			{
				vis[v] = true;
				q.push(v);
			}
		}
	}
}
int dsu[N];
int find(int x)
{
	if(dsu[x] != x)dsu[x] = find(dsu[x]);
	return dsu[x];
}
void soyuz(int a, int b)
{
	int pa = find(a), pb = find(b);
	if(pa != pb)dsu[pb] = pa;
}
int main()
{
	int T = read();
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		dsu[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int u = read(), v = read();
		add(u, v), add(v, u);
		soyuz(u, v);
	}
	for(int i = 1; i <= n; i++)
		if(!vis[i])bfs(i);
	for(int i = 1; i <= n; i++)
		if(weis[i] && schw[i])
			full[find(i)] = true;
	int q = read();
	for(int i = 1; i <= q; i++)
	{
		int s = read(), t = read();
		if(s == t)
		{
			puts("0");
			continue;
		}
		else if(find(s) != find(t))
		{
			puts("-1");
			continue;
		}
		else if(full[find(s)])
		{
			puts("1");
			continue;
		}
		if((weis[s] && weis[t]) || (schw[s] && schw[t]))puts("2");
		else puts("1");
	}
	return 0;
}