#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 2000010;
int n, m, k1, k2;
int ka[N], kb[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
vector<pair<int, int>>ans;
void tarjan(int p, int fa)
{
	dfn[p] = low[p] = ++cnt;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(!dfn[v])
		{
			tarjan(v, p);
			low[p] = min(low[p], low[v]);
			if(low[v] > dfn[p])
			{
				if(!ka[v] || !kb[v] || ka[v] == k1 || kb[v] == k2)
					ans.emplace_back(p, v);
			}
			ka[p] += ka[v], kb[p] += kb[v];
		}
		if(v != fa)low[p] = min(low[p], dfn[v]);
	}
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d%d", &n, &m, &k1, &k2);
	for(int i = 1; i <= k1; i++)
	{
		int k;
		scanf("%d", &k);
		ka[k]++;
	}
	for(int i = 1; i <= k2; i++)
	{
		int k;
		scanf("%d", &k);
		kb[k]++;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	tarjan(1, 0);
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d\n", i.first, i.second);
	return 0;
}
