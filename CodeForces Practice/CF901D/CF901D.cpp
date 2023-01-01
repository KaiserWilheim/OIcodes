#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], id[M], idx;
int eu[M], ev[M];
ll val[M], ans[M];
bool istr[N];
void add(int a, int b, int c)
{
	e[idx] = b, id[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
struct DSU
{
	int p[N];
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
			p[i] = i;
	}
	int find(int x)
	{
		if(p[x] != x)p[x] = find(p[x]);
		return p[x];
	}
	bool soyuz(int a, int b)
	{
		int fa = find(a), fb = find(b);
		if(fa != fb)
		{
			p[fa] = fb;
			return true;
		}
		else return false;
	}
};
DSU d;
int col[N];
void color()
{
	queue<int>q;
	q.push(1);
	col[1] = 2;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(col[e[i]])continue;
			col[e[i]] = col[u] ^ 1;
			q.push(e[i]);
		}
	}
}
void dfs1(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		ans[id[i]] += val[e[i]];
		val[p] -= val[e[i]];
		val[e[i]] = 0;
	}
}
int tmp[N];
void dfs2(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs2(e[i], p);
		tmp[p] -= tmp[e[i]];
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	d.init(n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &val[i]);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &eu[i], &ev[i]);
		if(!d.soyuz(eu[i], ev[i]))continue;
		add(eu[i], ev[i], i);
		add(ev[i], eu[i], i);
		istr[i] = true;
	}
	color();
	dfs1(1, 0);
	if(abs(val[1]) & 1)
	{
		puts("NO");
		return 0;
	}
	if(val[1] == 0)
	{
		puts("YES");
		for(int i = 1; i <= m; i++)
			printf("%lld\n", ans[i]);
		return 0;
	}
	for(int i = 1; i <= m; i++)
	{
		if(istr[i])continue;
		if(col[eu[i]] != col[ev[i]])continue;
		puts("YES");
		ll v = val[1] / 2;
		tmp[eu[i]]++;
		tmp[ev[i]]++;
		dfs2(1, 0);
		if(tmp[1] == 2)
		{
			val[eu[i]] -= v;
			val[ev[i]] -= v;
			ans[i] = v;
		}
		else
		{
			val[eu[i]] += v;
			val[ev[i]] += v;
			ans[i] = -v;
		}
		dfs1(1, 0);
		for(int j = 1; j <= m; j++)
			printf("%lld\n", ans[j]);
		return 0;
	}
	puts("NO");
	return 0;
}
