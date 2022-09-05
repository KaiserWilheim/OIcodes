#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010, M = 2000010, INF = 1e9;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}
bool bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof(d));
	q[0] = S, d[S] = 0, cur[S] = h[S];
	while(hh <= tt)
	{
		int u = q[hh++];
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if(v == T)return true;
				q[++tt] = v;
			}
		}
	}
	return false;
}
int find(int u, int limit)
{
	if(u == T)return limit;
	int flow = 0;
	for(int i = cur[u]; ~i && flow < limit; i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], limit - flow));
			if(!t)d[v] = -1;
			f[i] -= t, f[i ^ 1] += t;
			flow += t;
		}
	}
	return flow;
}
int dinic()
{
	int r = 0, flow;
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}
struct Missle
{
	int x, y, z;
	bool operator < (const Missle &a)const
	{
		return x == a.x ? (y == a.y ? z < a.z : y < a.y) : x < a.x;
	}
	bool operator > (const Missle &a)const
	{
		return x > a.x && y > a.y && z > a.z;
	}
}a[N];
int dp[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
	sort(a + 1, a + 1 + n);
	S = 0, T = n * 2 + 1;
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		dp[i] = 1;
		for(int j = 1; j < i; j++)
		{
			if(a[i] > a[j])
			{
				dp[i] = max(dp[i], dp[j] + 1);
				add(i, j + n, 1);
			}
		}
		ans = max(ans, dp[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		add(S, i, 1);
		add(i + n, T, 1);
	}
	int res = dinic();
	printf("%d\n%d\n", ans, n - res);
	return 0;
}