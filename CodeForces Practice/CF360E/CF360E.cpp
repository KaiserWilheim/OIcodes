#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 40010;
int n, m, k;
int s1, s2, f;
int h[N], e[M], ne[M], idx;
int *w[M];
int v[N], s[N], t[N], l[N], r[N];
void add(int a, int b, int *c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
struct Node
{
	int u;
	ll dis;
	Node(){}
	Node(int _u, ll _d) { u = _u, dis = _d; }
	bool operator < (const Node &rhs)const
	{
		return dis > rhs.dis;
	}
};
ll d1[N], d2[N];
void dijkstra(int s, ll *dis)
{
	for(int i = 1; i <= n; i++)
		dis[i] = 1e15;
	priority_queue<Node>q;
	dis[s] = 0;
	q.emplace(s, 0);
	while(!q.empty())
	{
		Node now = q.top();
		q.pop();
		if(dis[now.u] != now.dis)continue;
		int u = now.u;
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(dis[e[i]] > dis[u] + *w[i])
			{
				dis[e[i]] = dis[u] + *w[i];
				q.emplace(e[i], dis[e[i]]);
			}
		}
	}
}
bool solve(int d)
{
	bool flag = false;
	do
	{
		flag = false;
		dijkstra(s1, d1);
		dijkstra(s2, d2);
		for(int i = 1; i <= k; i++)
			if(v[i] == r[i] && d1[s[i]] < d2[s[i]] + d)
				v[i] = l[i], flag = true;
	} while(flag);
	return d1[f] < d2[f] + d;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	scanf("%d%d%d", &s1, &s2, &f);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, new int(w));
	}
	for(int i = 1; i <= k; i++)
	{
		scanf("%d%d%d%d", &s[i], &t[i], &l[i], &r[i]);
		v[i] = r[i];
		add(s[i], t[i], &v[i]);
	}
	for(int i = 1; i <= k; i++)
	{
		dijkstra(s1, d1);
		dijkstra(s2, d2);
		if(d1[s[i]] < d2[s[i]])v[i] = l[i];
	}
	if(solve(0))
	{
		puts("WIN");
		for(int i = 1; i <= k; i++)
			printf("%d ", v[i]);
		putchar('\n');
	}
	else if(solve(1))
	{
		puts("DRAW");
		for(int i = 1; i <= k; i++)
			printf("%d ", v[i]);
		putchar('\n');
	}
	else puts("LOSE");
	return 0;
}
