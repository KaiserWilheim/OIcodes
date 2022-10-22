#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool vis[N], col[N];
int dfn[N], cnt;
bool chq()
{
	queue<int>q;
	q.push(1);
	vis[1] = true;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			if(vis[e[i]])continue;
			vis[e[i]] = true;
			q.push(e[i]);
		}
	}
	bool flag = true;
	for(int i = 1; i <= n; i++)
		flag &= vis[i], vis[i] = false;
	return flag;
}
void dfs(int p, int fa)
{
	dfn[++cnt] = p;
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		dfs(e[i], p);
	}
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		h[i] = -1;
		vis[i] = false;
		col[i] = false;
		dfn[i] = 0;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	if(!chq())
	{
		puts("NO");
		return;
	}
	dfs(1, 0);
	vector<int>ans;
	for(int i = 1; i <= n; i++)
	{
		bool flag = false;
		int p = dfn[i];
		for(int j = h[p]; ~j; j = ne[j])
			flag |= col[e[j]];
		col[p] = !flag;
		if(!flag)ans.push_back(p);
	}
	puts("YES");
	printf("%d\n", ans.size());
	for(int i : ans)
		printf("%d ", i);
	putchar('\n');
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = cnt = 0;
		solve();
	}
	return 0;
}