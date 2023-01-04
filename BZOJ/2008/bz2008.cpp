#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = 100010;
int n, m;
int h[N], e[M], ne[M], idx;
int deg[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int ans[N], tot;
int tmp[N];
vector<int>v[N];
void solve(int u)
{
	int q[N];
	int hh = 1, tt = 0;
	for(int i = 1; i <= n; i++)tmp[i] = deg[i] + 1;
	for(int t = n; t; t--)
	{
		if(!v[t].empty())
		{
			for(auto j : v[t])
			{
				if(!(--tmp[j]))
				{
					q[++tt] = j;
					if(hh < tt && q[tt - 1] == u)swap(q[tt], q[tt - 1]);
				}
			}
		}
		int p = q[hh++];
		if(p == u)
		{
			printf("%d ", t);
			break;
		}
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(!(--tmp[e[i]]))
			{
				q[++tt] = e[i];
				if(hh < tt && q[tt - 1] == u)swap(q[tt], q[tt - 1]);
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		v[x].push_back(i);
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		deg[u]++;
		add(v, u);
	}
	priority_queue<int>q;
	for(int i = 1; i <= n; i++)tmp[i] = deg[i] + 1;
	for(int t = n; t; t--)
	{
		if(!v[t].empty())
		{
			for(auto j : v[t])
			{
				tmp[j]--;
				if(!tmp[j])q.push(j);
			}
		}
		int u = q.top();
		q.pop();
		ans[t] = u;
		for(int i = h[u]; ~i; i = ne[i])
			if(!(--tmp[e[i]]))q.push(e[i]);
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	for(int i = 1; i <= n; i++)
		solve(i);
	putchar('\n');
	return 0;
}