#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
const ll mod = 998244353;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int odd[N << 3], even[N << 3], rev[N << 3];
void reverse(int p, int l, int r)
{
	if(l == r)
	{
		if(l & 1)odd[p] ^= 1;
		else even[p] ^= 1;
	}
	else
	{
		odd[p] = (r + 1) / 2 - l / 2 - odd[p];
		even[p] = r / 2 - (l - 1) / 2 - even[p];
	}
	rev[p] ^= 1;
}
void pushup(int p)
{
	odd[p] = odd[p << 1] + odd[p << 1 | 1];
	even[p] = even[p << 1] + even[p << 1 | 1];
}
void pushdown(int p, int l, int r)
{
	int mid = (l + r) >> 1;
	reverse(p << 1, l, mid);
	reverse(p << 1 | 1, mid + 1, r);
	rev[p] = 0;
}
void segchg(int p, int l, int r, int ql, int qr)
{
	if(l >= ql && r <= qr)
	{
		reverse(p, l, r);
		return;
	}
	if(rev[p])pushdown(p, l, r);
	int mid = (l + r) >> 1;
	if(ql <= mid)segchg(p << 1, l, mid, ql, qr);
	if(qr > mid)segchg(p << 1 | 1, mid + 1, r, ql, qr);
	pushup(p);
}
vector<int>v[N];
int sz[N], son[N];
int fdis[N];
void dfs1(int p, int fa)
{
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		fdis[e[i]] = w[i];
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
ll ans;
ll get()
{
	ll res = ((m / 2 + 1 - even[1]) * even[1] % mod + ((m + 1) / 2 - odd[1]) * odd[1] % mod) % mod;
	return res;
}
void calc(int p, int fa, int tar)
{
	for(int i = 0; i < v[p].size(); i++)
		segchg(1, 1, m, v[p][i], m);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || e[i] == tar)continue;
		calc(e[i], p, tar);
	}
}
void dfs2(int p, int fa, int op)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa || e[i] == son[p])continue;
		dfs2(e[i], p, 0);
	}
	if(son[p])dfs2(son[p], p, 1);
	calc(p, fa, son[p]);
	ans = (ans + fdis[p] * get() % mod) % mod;
	if(!op)calc(p, fa, 0);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		v[x].push_back(i);
	}
	dfs1(1, 0);
	dfs2(1, 0, 1);
	printf("%lld\n", ans);
	return 0;
}
