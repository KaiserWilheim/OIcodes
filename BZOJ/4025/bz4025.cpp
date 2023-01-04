#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll mod = 998244353;
int n, m, q;
struct Node
{
	int x, y, s, t;
};
Node e[M];
int ans[N];
vector<int>tr[N << 3];
void add(int p, int l, int r, int ql, int qr, int id)
{
	if(l >= ql && r <= qr)
	{
		tr[p].push_back(id);
		return;
	}
	int mid = (l + r) >> 1;
	if(ql <= mid)add(p << 1, l, mid, ql, qr, id);
	if(qr > mid)add(p << 1 | 1, mid + 1, r, ql, qr, id);
}
int fa[N], d[N], sz[N];
int flag[M], cnt;
struct op
{
	int id, x, y;
};
op sta[M];
int tt;
void insert(int id)
{
	int x = e[id].x, y = e[id].y,
		fx = x, fy = y,
		cx = d[x], cy = d[y];
	while(fx != fa[fx])fx = fa[fx], cx ^= d[fx];
	while(fy != fa[fy])fy = fa[fy], cy ^= d[fy];
	if(fx == fy)
	{
		if(cx == cy)flag[id] = 3, cnt++;
		else flag[id] = 2;
	}
	else
	{
		flag[id] = 1;
		if(sz[fx] < sz[fy])swap(fx, fy), swap(cx, cy);
		sz[fx] += sz[fy], d[fy] ^= cx ^ cy ^ 1, fa[fy] = fx;
	}
	sta[++tt] = { id,fx,fy };
}
void erase()
{
	int id = sta[tt].id, x = sta[tt].x, y = sta[tt].y,
		tmp = flag[id];
	tt--;
	flag[id] = 0;
	if(tmp == 3)cnt--;
	if(tmp ^ 1)return;
	fa[y] = y, d[y] = 0, sz[x] -= sz[y];
}
void dfs(int p, int l, int r)
{
	int len = tr[p].size();
	for(int i = 0; i < len; i++)insert(tr[p][i]);
	int mid = (l + r) >> 1;
	if(l == r)ans[l] = cnt;
	else dfs(p << 1, l, mid), dfs(p << 1 | 1, mid + 1, r);
	for(int i = 0; i < len; i++)erase();
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= m; i++)
	{
		int x, y, s, t;
		scanf("%d%d%d%d", &x, &y, &s, &t);
		e[i] = { x,y,s,t };
		add(1, 1, q, s + 1, t, i);
	}
	for(int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;
	dfs(1, 1, q);
	for(int i = 1; i <= q; i++)
		puts(ans[i] ? "No" : "Yes");
	return 0;
}
