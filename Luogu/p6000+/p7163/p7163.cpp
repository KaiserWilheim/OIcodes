#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int rt;
int h[N], e[M], ne[M], idx;
bool ison[N], full[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int p, int fa)
{
	full[p] = ison[p];
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		full[p] = (full[p] && full[e[i]]);
	}
}
ll f[3][N][2];
inline ll min4(ll a, ll b, ll c, ll d)
{
	return min(min(a, b), min(c, d));
}
inline ll min6(ll a, ll b, ll c, ll d, ll e, ll f)
{
	return min(min(min(a, b), c), min(min(d, e), f));
}
void dfs2(int p, int fa)
{
	f[0][p][ison[p]] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa || full[v])continue;
		dfs2(v, p);
		ll f0 = f[0][p][0], f1 = f[0][p][1],
			g0 = f[1][p][0], g1 = f[1][p][1],
			h0 = f[2][p][0], h1 = f[2][p][1];
		f[0][p][1] = min(f0 + f[0][v][0] + 2, f1 + f[0][v][1] + 4);
		f[0][p][0] = min(f1 + f[0][v][0] + 2, f0 + f[0][v][1] + 4);
		f[1][p][1] = min4(g0 + f[0][v][0] + 2, g1 + f[0][v][1] + 4, f0 + f[1][v][1] + 1, f1 + f[1][v][0] + 3);
		f[1][p][0] = min4(g1 + f[0][v][0] + 2, g0 + f[0][v][1] + 4, f1 + f[1][v][1] + 1, f0 + f[1][v][0] + 3);
		f[2][p][1] = min6(f0 + f[2][v][0] + 2, f1 + f[2][v][1] + 4, g0 + f[1][v][0] + 2, g1 + f[1][v][1], h0 + f[0][v][0] + 2, h1 + f[0][v][1] + 4);
		f[2][p][0] = min6(f1 + f[2][v][0] + 2, f0 + f[2][v][1] + 4, g1 + f[1][v][0] + 2, g0 + f[1][v][1], h1 + f[0][v][0] + 2, h0 + f[0][v][1] + 4);
	}
	f[1][p][0] = min(f[1][p][0], f[0][p][1] + 1);
	f[1][p][1] = min(f[1][p][1], f[0][p][0] + 1);
	f[2][p][0] = min(f[2][p][0], f[1][p][0]);
	f[2][p][1] = min(f[2][p][1], f[1][p][1]);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	string s;
	cin >> s;
	for(int i = 1; i <= n; i++)
		ison[i] = (s[i - 1] == '1');
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	rt = 1;
	for(int i = 1; i <= n; i++)
		if(!ison[i]) { rt = i; break; }
	dfs1(rt, 0);
	memset(f, 63, sizeof(f));
	dfs2(rt, 0);
	printf("%lld\n", f[2][rt][1]);
	return 0;
}