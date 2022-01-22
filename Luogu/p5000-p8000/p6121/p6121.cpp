#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
struct _edge
{
	int from, to, next;
}e[N << 1];
int tot, h[N], k;
bool vis[N];
void add(int from, int to)
{
	e[++tot].from = from;
	e[tot].to = to;
	e[tot].next = h[from];
	h[from] = tot;
}
int n, m, u, v, t[N], ans[N], f[N];
int find(int x)
{
	while(x != f[x]) x = f[x] = f[f[x]];
	return x;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	for(int i = 1; i <= n; i++)scanf("%d", &t[i]);
	for(int i = 1; i <= n; i++)f[i] = i;
	vis[t[n]] = 1;
	ans[n] = 1;
	for(int i = n - 1; i >= 1; i--)
	{
		vis[t[i]] = 1;
		for(int j = h[t[i]]; j; j = e[j].next)
		{
			if(vis[e[j].to] == 1)
			{
				int fx = find(t[i]), fy = find(e[j].to);
				if(fx != fy)
				{
					++k;
					f[fx] = fy;
				}
			}
		}
		if(k == n - i) ans[i] = 1;
		else ans[i] = 0;
	}
	for(int i = 1; i <= n; i++)
	{
		if(ans[i] == 1) puts("YES");
		else puts("NO");
	}
	return 0;
}
