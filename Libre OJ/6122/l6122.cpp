#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, INF = 1e8;
int n, m;
map<string, int>dic;
struct edge
{
	int next, to, fl, v;
}e[N << 1];
int h[N], idx = 1;
int dist[N], pre[N], vis[N], minn[N];
queue<int>q;
int s, t, val, flag[N], check;
string ss[N];

void add(int from, int to, int fl, int v)
{
	e[++idx].to = to; e[idx].next = h[from]; e[idx].fl = fl; e[idx].v = v; h[from] = idx;
}

void update(int x, int flow)
{
	e[pre[x]].fl -= flow;
	e[pre[x] ^ 1].fl += flow;
	if(e[pre[x] ^ 1].to)update(e[pre[x] ^ 1].to, flow);
}

int spfa()
{
	memset(vis, 0, sizeof(vis));
	while(!q.empty())q.pop();
	for(int i = 1; i <= t; i++)dist[i] = -INF;
	minn[s] = INF; dist[s] = 0; q.push(s); vis[s] = 1;
	while(!q.empty())
	{
		int x = q.front(); q.pop(); vis[x] = 0;
		for(int i = h[x]; i; i = e[i].next)
		{
			if(dist[e[i].to] < dist[x] + e[i].v && e[i].fl)
			{
				dist[e[i].to] = dist[x] + e[i].v;
				pre[e[i].to] = i;
				minn[e[i].to] = min(minn[x], e[i].fl);
				if(!vis[e[i].to])
				{
					vis[e[i].to] = 1;
					q.push(e[i].to);
				}
			}
		}
	}
	if(dist[t] == -INF)return -INF;
	update(t, minn[t]); val += minn[t];
	return minn[t] * dist[t];
}

int EK()
{
	int sum = 0;
	while(1)
	{
		int x = spfa();
		if(x == -INF)return sum;
		sum += x;
	}
}

void dfs1(int x)
{
	cout << ss[x] << endl;
	vis[x] = 1;
	for(int i = h[x]; i; i = e[i].next)
	{
		if(e[i].to > n && e[i].to <= 2 * n && e[i].fl == 0) { dfs1(e[i].to - n); break; }//第一次dfs只找一条路径，找到就break
	}
}

void dfs2(int x)
{
	vis[x] = 1;
	for(int i = h[x]; i; i = e[i].next)
	{
		if(e[i].to > n && e[i].to <= 2 * n && e[i].fl == 0 && !vis[e[i].to - n]) { dfs2(e[i].to - n); }//不走第一次路径走过的点
	}
	cout << ss[x] << endl;
}

int main()
{
	scanf("%d%d", &n, &m);
	t = n * 2 + 1;
	for(int i = 1; i <= n; i++)
	{
		cin >> ss[i];
		dic[ss[i]] = i;
	}
	for(int i = 1; i <= m; i++)
	{
		string s1, s2;
		cin >> s1 >> s2;
		int x = dic[s1], y = dic[s2];
		if(x > y)swap(x, y);
		if(x == 1 && y == n)check = 1;
		add(x, y + n, 1, 0);
		add(y + n, x, 0, 0);
	}
	add(s, n + 1, INF, 0);
	add(n + 1, s, 0, 0);
	add(n, t, INF, 0);
	add(t, n, 0, 0);
	for(int i = 1; i <= n; i++)
	{
		if(i != 1 && i != n) { add(i + n, i, 1, 1), add(i, i + n, 0, -1); }
		else { add(i + n, i, 2, 1), add(i, i + n, 0, -1); }
	}
	int maxflow = EK();
	if(val == 2)
	{
		printf("%d\n", maxflow - 2);
	}
	else if(val == 1 && check)
	{
		printf("%d\n", 2);
		cout << ss[1] << endl << ss[n] << endl << ss[1] << endl;
		return 0;
	}
	else
	{
		printf("No Solution!\n");
		return 0;
	}
	memset(vis, 0, sizeof(vis));
	dfs1(1);
	dfs2(1);
	return 0;
}
