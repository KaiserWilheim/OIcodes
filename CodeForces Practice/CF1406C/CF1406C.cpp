#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
int sz[N], msz[N], fa[N];
bool leaf[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int father)
{
	sz[p] = 1, fa[p] = father;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == father)continue;
		dfs(e[i], p);
		sz[p] += sz[e[i]];
		msz[p] = max(msz[p], sz[e[i]]);
	}
	if(sz[p] == 1)leaf[p] = true;
	msz[p] = max(msz[p], n - sz[p]);
}
void solve()
{
	memset(h, -1, sizeof(h));
	memset(msz, 0, sizeof(msz));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	int maxn = 1919810;
	int l = 0, r = 0;
	for(int i = 1; i <= n; i++)
		maxn = min(maxn, msz[i]);
	for(int i = 1; i <= n; i++)
		if(msz[i] == maxn)
			l = r, r = i;
	if(!l)
	{
		printf("%d %d\n", r, e[h[r]]);
		printf("%d %d\n", r, e[h[r]]);
	}
	else
	{
		memset(leaf, false, sizeof(leaf));
		dfs(l, r);
		int k;
		for(int i = 1; i <= n; i++)
		{
			if(leaf[i])
			{
				k = i;
				break;
			}
		}
		printf("%d %d\n", k, fa[k]);
		printf("%d %d\n", r, k);
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = 0;
		solve();
	}
	return 0;
}