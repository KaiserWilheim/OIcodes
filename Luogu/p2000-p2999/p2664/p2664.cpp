#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010, M = N << 1;
int n;
bool vis[N];
int col[N], sum;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int sz[N], siz[N];
int mns[N], tmp[N];
void dfs(int p, int fa)
{
	sz[p] = 1;
	int tmp = mns[col[fa]];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		sz[p] += sz[e[i]];
	}
	mns[col[p]]++;
	if(fa)
	{
		siz[p] = sz[p] - mns[col[fa]] + tmp;
		mns[col[fa]] += siz[p];
	}
}
int tot;
int ans[N];
void getans(int p, int fa)
{
	int ltmp = tmp[col[fa]];
	tot += siz[p] - tmp[col[fa]];
	tmp[col[fa]] = siz[p];
	ans[p] = n * sum - tot + tmp[col[p]];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		getans(e[i], p);
	}
	tmp[col[fa]] = ltmp;
	tot -= siz[p] - tmp[col[fa]];
}
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &col[i]);
		if(!vis[col[i]])vis[col[i]] = true, sum++;
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%lld%lld", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i < N; i++)
	{
		if(vis[i])
		{
			tot += n - mns[i];
			tmp[i] = n - mns[i];
		}
	}
	getans(1, 0);
	for(int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
