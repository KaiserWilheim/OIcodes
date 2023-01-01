#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int top[N], bel[N], cnt;
int sta[N];
int sz;
void dfs(int p, int fa)
{
	int cur = sz;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		if(sz - cur >= m)
		{
			top[++cnt] = p;
			while(sz > cur)
				bel[sta[sz--]] = cnt;
		}
	}
	sta[++sz] = p;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	if(!cnt)top[++cnt] = 1;
	while(sz)bel[sta[sz--]] = cnt;
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		printf("%d ", bel[i]);
	putchar('\n');
	for(int i = 1; i <= cnt; i++)
		printf("%d ", top[i]);
	putchar('\n');
	return 0;
}