#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 2000010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
struct LTable
{
	int l, r;
}p[N << 2];
int w[N], q[N], d[N];
void push(int x)
{
	p[x].r = p[N + w[x]].r;
	p[p[x].r].l = x;
	p[x].l = N + w[x];
	p[p[x].l].r = x;
}
void pop(int x)
{
	p[p[x].r].l = p[x].l;
	p[p[x].l].r = p[x].r;
}
bool vis[N];
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
	for(int i = 1; i <= n; i++)push(i);
	int now = 0, ans = 0;
	for(int k = n; k; k--, now++)
	{
		while(!p[N + now].r)now--;
		int x = p[N + now].r;
		pop(x);
		q[k] = x, d[x] = k;
		for(int i = h[x]; ~i; i = ne[i])
		{
			if(!d[e[i]])
			{
				pop(e[i]);
				++w[e[i]];
				push(e[i]);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(vis[q[i]])continue;
		ans++;
		vis[q[i]] = 1;
		for(int j = h[q[i]]; ~j; j = ne[j])
			vis[e[j]] = 1;
	}
	printf("%d\n", ans);
	return 0;
}
