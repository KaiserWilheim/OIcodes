#include<bits/stdc++.h>
using namespace std;
const int N = 510, M = 200010, INF = 1e8;
int n, f, d;
int h[N], e[M], c[M], ne[M], idx;
int num[N];
int minn, s, t, minflow, maxflow, tot;
queue<int>q;

void add(int u, int v, int a)
{
	e[++idx] = v, c[idx] = a, ne[idx] = h[u], h[u] = idx;
	e[++idx] = u, c[idx] = 0, ne[idx] = h[v], h[v] = idx;
}

bool add_num()
{
	while(!q.empty())q.pop();
	for(int i = s; i <= t + n; i++)num[i] = -1;
	num[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		for(int i = h[now]; i; i = ne[i])
		{
			if(c[i] && num[e[i]] == -1)
			{
				num[e[i]] = num[now] + 1;
				q.push(e[i]);
			}
		}
	}
	if(num[t] == -1)return false;
	else return true;
}

int dfs(int u, int s)
{
	if(u == t)
	{
		return s;
	}
	for(int i = h[u]; i; i = ne[i])
	{
		if(c[i] && num[u] + 1 == num[e[i]] && (minflow = dfs(e[i], min(s, c[i]))))
		{
			c[i] -= minflow;
			c[i ^ 1] += minflow;
			return minflow;
		}
	}
	return 0;
}

void dinic()
{
	while(add_num())
		while((minn = dfs(1, INF)))
			maxflow += minn;
}

int main()
{
	scanf("%d%d%d", &n, &f, &d);
	idx = 1;
	s = 1;
	t = 1 + f + n + d + 1;
	for(int i = 1; i <= f; i++)add(s, 1 + i, 1);
	for(int i = 1; i <= d; i++)add(1 + f + n + i, t, 1);
	for(int i = 1; i <= n; i++)add(1 + f + i, 1 + f + n + d + 1 + i, 1);
	for(int i = 1; i <= n; i++)
	{
		int dn, fn;
		scanf("%d%d", &fn, &dn);
		for(int q = 1; q <= fn; q++)
		{
			int fi;
			scanf("%d", &fi);
			add(1 + fi, 1 + f + i, 1);
		}
		for(int q = 1; q <= dn; q++)
		{
			int di;
			scanf("%d", &di);
			add(1 + f + n + d + 1 + i, 1 + f + n + di, 1);
		}
	}
	dinic();
	printf("%d\n", maxflow);
	return 0;
}
