#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
const int INF = 1e9;
int n, m;
int c[N], p[N];
int f[M], g[M];
int flow[N], ans;
void upd(int &a, int &b, int x, int y)
{
	if(x < a)a = x, b = y;
}
int sgn(int x) { return x < 0 ? -1 : 1; }
void update(int x)
{
	f[x] = INF;
	if(c[x])f[x] = 0, g[x] = x;
	upd(f[x], g[x], f[x << 1] + sgn(flow[x << 1]), g[x << 1]);
	upd(f[x], g[x], f[x << 1 | 1] + sgn(flow[x << 1 | 1]), g[x << 1 | 1]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%d", &c[i]);
	for(int i = 1; i <= m; i++)scanf("%d", &p[i]);
	for(int i = 1; i <= 3 * n; i++)f[i] = INF;
	for(int i = n; i; i--)update(i);
	for(int i = 1; i <= m; i++)
	{
		int x = INF, y = 0, u = p[i], t = 0, v = 0;
		while(u)
		{
			if(x > f[u] + t)x = f[u] + t, y = g[u], v = u;
			t += -sgn(flow[u] - 1);
			u >>= 1;
		}
		u = p[i];
		ans += x;
		while(u != v)
		{
			flow[u]--;
			update(u >> 1);
			u >>= 1;
		}
		c[y]--;
		update(y);
		while(y != v)
		{
			flow[y]++;
			update(y >> 1);
			y >>= 1;
		}
		while(v)
		{
			update(v);
			v >>= 1;
		}
		printf("%d ", ans);
	}
	return 0;
}
