#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int tag[N];
int rt = 0;
bool vis[N];
int a[N << 2];
int ans = 0;
void dfs(int p, int fa)
{
	vis[p] = true, a[++ans] = p, tag[p] ^= 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		dfs(e[i], p);
		a[++ans] = p;
		tag[p] ^= 1;
	}
	if(tag[p])
	{
		a[++ans] = fa;
		tag[fa] ^= 1;
		a[++ans] = p;
		tag[p] ^= 1;
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &tag[i]);
		if(tag[i])rt = i;
	}
	if(rt)dfs(rt, 0);
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i] && tag[i])
		{
			puts("-1");
			return 0;
		}
	}
	if(ans > 1 && a[ans - 1] == 0)ans -= 3;
	printf("%d\n", ans);
	for(int i = 1; i <= ans; i++)
		printf("%d ", a[i]);
	putchar('\n');
	return 0;
}