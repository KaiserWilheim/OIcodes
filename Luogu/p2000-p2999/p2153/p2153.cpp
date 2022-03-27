#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 810;
const int INF = 1e18;
int S, T;
struct node
{
	int y, z, w, nex;
} e[20010 * 4];
int head[maxn * 2], tot = 1, hd[maxn * 2];
int n, m;
void add(int x, int y, int z, int w)
{
	e[++tot] = { y, z, w, head[x] };
	head[x] = tot;
}
int ans, cost;
int d[maxn], vis[maxn];
bool spfa()
{
	queue<int> q;
	memset(d, 0x3f, sizeof(d));
	memset(vis, 0, sizeof(vis));
	d[S] = 0;
	q.push(S);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for(int i = head[x]; i; i = e[i].nex)
		{
			int v = e[i].y;
			if(e[i].z && d[v] > d[x] + e[i].w)
			{
				d[v] = d[x] + e[i].w;
				if(!vis[v])
					vis[v] = 1, q.push(v);
			}
		}
	}
	return d[T] != 0x3f3f3f3f3f3f3f3f;
}
int dfs(int x, int in)
{
	if(x == T || !in)
		return in;
	int out = 0;
	vis[x] = 1;
	for(int &i = hd[x]; i && in; i = e[i].nex)
	{
		int v = e[i].y;
		if(!e[i].z || d[v] != d[x] + e[i].w || vis[v])
			continue;
		int res = dfs(v, min(in, e[i].z));
		e[i].z -= res;
		e[i ^ 1].z += res;
		out += res;
		in -= res;
	}
	return out;
}
void dinic()
{
	while(spfa())
	{
		memcpy(hd, head, sizeof(head));
		int k = dfs(S, INF);
		ans += k;
		cost += k * d[T];
	}
}
signed main()
{
	cin >> n >> m;
	while(m--)
	{
		int x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		add(x + n, y, 1, z);
		add(y, x + n, 0, -z);
	}
	for(int i = 1; i <= n; i++)
		add(i, i + n, 1, 0), add(i + n, i, 0, 0);
	S = 1 + n, T = n;
	dinic();
	printf("%lld %lld", ans, cost);
	return 0;
}
