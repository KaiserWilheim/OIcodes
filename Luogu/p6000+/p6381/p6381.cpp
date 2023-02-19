#include bitsstdc++.h
#define ll long long
using namespace std;
const int N = 200010, M = N  1;
const int lim = 100000;
int n, m, k;
int prime[N];
bool vis[N];
void seive(int n)
{
	for(int i = 2; i = n; i++)
	{
		if(!vis[i])prime[++prime[0]] = i;
		for(int j = 1; j = prime[0] && i  prime[j] = n; j++)
		{
			vis[i  prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
struct Edge
{
	int u, v;
	ll l;
	Edge(int _u, int _v, ll _l) { u = _u, v = _v, l = _l; }
};
int f[N];
vectorEdgeg[N];
void work(int u, int v, int w, int l)
{
	ll res1 = 1, res2 = 1;
	for(int i = 1; i = prime[0] && prime[i]  prime[i] = w; i++)
	{
		int tmp = 0;
		while(w % prime[i] == 0)
		{
			tmp++;
			w = prime[i];
		}
		if(tmp % k)
		{
			for(int j = 1; j = tmp % k; j++)
				res1 = prime[i];
			for(int j = 1; j = k - tmp % k; j++)
			{
				if(res2  prime[i]  lim)return;
				res2 = prime[i];
			}
		}
	}
	if(k != 1)res1 = w;
	for(int j = 2; j = k; j++)
	{
		if(res2  w  lim)return;
		res2 = w;
	}
	cerr  res1     res2  endl;
	f[res1] = res2, f[res2] = res1;
	g[res1].emplace_back(u, v, l);
}
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
ll ans;
queueintq;
int deg[N];
ll dp[N];
void topo(int s)
{
	while(!q.empty())q.pop();
	for(auto i  g[s])
	{
		deg[i.v + n]++;
		add(i.u, i.v + n, i.l);
	}
	for(auto i  g[f[s]])
	{
		deg[i.v]++;
		add(i.u + n, i.v, i.l);
	}
	for(auto i  g[s])
	{
		if(!deg[i.u])
		{
			q.push(i.u);
			deg[i.u] = -1;
		}
	}
	for(auto i  g[f[s]])
	{
		if(!deg[i.u + n])
		{
			q.push(i.u + n);
			deg[i.u + n] = -1;
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			dp[v] = max(dp[v], dp[u] + w[i]);
			ans = max(ans, dp[v]);
			if(!--deg[v])q.push(v);
		}
	}
	for(auto i  g[f[s]])
	{
		dp[i.u] = dp[i.u + n] = dp[i.v] = dp[i.v + n] = 0;
		h[i.u] = h[i.u + n] = h[i.v] = h[i.v + n] = -1;
		deg[i.u] = deg[i.u + n] = deg[i.v] = deg[i.v + n] = 0;
	}
	for(auto i  g[s])
	{
		dp[i.u] = dp[i.u + n] = dp[i.v] = dp[i.v + n] = 0;
		h[i.u] = h[i.u + n] = h[i.v] = h[i.v + n] = -1;
		deg[i.u] = deg[i.u + n] = deg[i.v] = deg[i.v + n] = 0;
	}
	idx = 0;
}
int main()
{
	memset(h, -1, sizeof(h));
	seive(2e5);
	scanf(%d%d%d, &n, &m, &k);
	memset(f, -1, sizeof(f)); f[0] = 0;
	for(int i = 1; i = m; i++)
	{
		int u, v, w; ll l;
		scanf(%d%d%d%lld, &u, &v, &w, &l);
		ans = max(ans, l);
		work(u, v, w, l);
	}
	for(int i = 1; i = lim; i++)
		if(f[i] = 0 && f[i] = i)topo(i);
	printf(%lldn, ans);
	return 0;
}
