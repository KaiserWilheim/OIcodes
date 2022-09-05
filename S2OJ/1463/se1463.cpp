#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010, M = N << 1;
const ll mod = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int h[N], e[M], ne[M], idx;
ll w[M];
int deg[N];
void add(int a, int b, ll c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
	deg[b]++;
}
int dep[N];
ll rk[N];
ll ans[N];
queue<int>q;
vector<int>g[N];
pair<ll, ll>f[N];
bool cmp(int a, int b)
{
	return f[a] < f[b];
}
void topo()
{
	for(int i = 1; i <= n; i++)
	{
		if(!deg[i])q.push(i), dep[i] = 1, f[i] = make_pair(0, 0);
		else f[i] = make_pair(INF, INF);
	}
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		g[dep[p]].push_back(p);
		for(int i = h[p]; ~i; i = ne[i])
		{
			int j = e[i];
			dep[j] = max(dep[j], dep[p] + 1);
			if(--deg[j] == 0)q.push(j);
		}
	}
	for(int k = 1; k <= n; k++)
	{
		for(auto p : g[k])
		{
			for(int i = h[p]; ~i; i = ne[i])
			{
				int j = e[i];
				if(dep[p] + 1 == dep[j])
				{
					pair<ll, ll> v = make_pair(w[i], rk[p]);
					if(v < f[j])
					{
						f[j] = v;
						ans[j] = (ans[p] * 29 + w[i]) % mod;
					}
				}
			}
		}
		sort(g[k + 1].begin(), g[k + 1].end(), cmp);
		int i = 0;
		for(auto p : g[k + 1])rk[p] = i++;
	}
	for(int i = 1; i <= n; i++)
	{
		if(deg[i])puts("Infinity");
		else printf("%lld\n", 29 * ans[i] % mod);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		ll c;
		scanf("%d%d%lld", &a, &b, &c);
		add(b, a, c);
	}
	topo();
	return 0;
}