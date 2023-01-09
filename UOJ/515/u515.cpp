#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int a[N];
struct SegTree
{
	int l, r;
	int maxn, maxs;
	int cnt;
};
SegTree tr[N << 3];
void pushup(int p)
{
	if(tr[p << 1].maxn > tr[p << 1 | 1].maxn)
	{
		tr[p].maxn = tr[p << 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxs, tr[p << 1 | 1].maxn);
	}
	else if(tr[p << 1].maxn < tr[p << 1 | 1].maxn)
	{
		tr[p].maxn = tr[p << 1 | 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxn, tr[p << 1 | 1].maxs);
	}
	else
	{
		tr[p].maxn = tr[p << 1].maxn;
		tr[p].maxs = max(tr[p << 1].maxs, tr[p << 1 | 1].maxs);
	}
}
void pushdown(int p)
{
	if(tr[p << 1].maxn > tr[p].maxn)
		tr[p << 1].maxn = tr[p].maxn, tr[p << 1].cnt += tr[p].cnt;
	if(tr[p << 1 | 1].maxn > tr[p].maxn)
		tr[p << 1 | 1].maxn = tr[p].maxn, tr[p << 1 | 1].cnt += tr[p].cnt;
	tr[p].cnt = 0;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].maxn = 1e9, tr[p].maxs = -1;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	//pushup(p);
}
void segmin(int p, int l, int r, int k)
{
	if(k >= tr[p].maxn)return;
	if(tr[p].l >= l && tr[p].r <= r && k > tr[p].maxs)
	{
		tr[p].maxn = k;
		tr[p].cnt++;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segmin(p << 1, l, r, k);
	if(r > mid)segmin(p << 1 | 1, l, r, k);
	pushup(p);
}
int segsum(int p, int pos)
{
	if(tr[p].l == tr[p].r)return tr[p].cnt;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)return segsum(p << 1, pos);
	else return segsum(p << 1 | 1, pos);
}
int ans[N];
vector<int>q[N];
vector<pair<int, int>>e[N];
int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
	{
		a[i] = read();
		e[i].emplace_back(0, a[i]);
	}
	build(1, 0, m);
	for(int i = 1; i <= m; i++)
	{
		ans[i] = -1;
		int op, x, v;
		op = read(), x = read();
		if(op == 1)
		{
			v = read();
			e[x].emplace_back(i, v);
		}
		else q[x].push_back(i);
	}
	for(int i = n; i; i--)
	{
		if(!e[i].empty())
		{
			for(int j = 0; j < e[i].size() - 1; j++)
				segmin(1, e[i][j].first, e[i][j + 1].first - 1, e[i][j].second);
			segmin(1, e[i][e[i].size() - 1].first, m, e[i][e[i].size() - 1].second);
		}
		for(int v : q[i])
			ans[v] = segsum(1, v);
	}
	for(int i = 1; i <= m; i++)
		if(ans[i] != -1)printf("%d\n", ans[i]);
	return 0;
}
