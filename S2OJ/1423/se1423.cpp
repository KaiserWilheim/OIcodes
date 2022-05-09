#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N];
struct query
{
	int l, r, id;
	friend bool operator < (const query &a, const query &b)
	{
		return a.r < b.r;
	}
}b[N];
int ans[N];
int pos[N];
vector<int>v[N];
void divide(int x)
{
	int i;
	for(i = 1; i * i < x; i++)
		if(x % i == 0)
			v[x].push_back(i), v[x].push_back(x / i);
	if(i * i == x)v[x].push_back(i);
}
namespace Segtree
{
	struct SegTree
	{
		int l, r;
		int sum, tag;
	}tr[N << 3];

	void pushup(int p)
	{
		tr[p].sum = max(tr[p << 1].sum, tr[p << 1 | 1].sum);
	}
	void pushdown(int p)
	{
		auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
		left.sum = max(left.sum, root.tag);
		left.tag = max(left.tag, root.tag);
		rght.sum = max(rght.sum, root.tag);
		rght.tag = max(rght.tag, root.tag);
		root.tag = 0;
	}

	void build(int p, int l, int r)
	{
		tr[p].l = l, tr[p].r = r;
		if(l == r)
		{
			tr[p].sum = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushup(p);
	}

	void segadd(int p, int l, int r, int k)
	{
		if(tr[p].l >= l && tr[p].r <= r)
		{
			tr[p].sum = max(tr[p].sum, k);
			tr[p].tag = max(tr[p].tag, k);
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)segadd(p << 1, l, r, k);
		if(r > mid)segadd(p << 1 | 1, l, r, k);
		pushup(p);
	}
	int segmax(int p, int l, int r)
	{
		if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
		if(tr[p].tag)pushdown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		int res = 0;
		if(l <= mid)res = max(res, segmax(p << 1, l, r));
		if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
		return res;
	}
}
using namespace Segtree;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &b[i].l, &b[i].r);
		b[i].id = i;
	}
	sort(b + 1, b + 1 + m);
	for(int i = 1; i <= n; i++)divide(a[i]);
	Segtree::build(1, 1, n);
	int now = 1;
	for(int i = 1; i <= n; i++)
	{
		for(auto j : v[a[i]])
		{
			if(pos[j])Segtree::segadd(1, 1, pos[j], j);
			pos[j] = i;
		}
		while(i == b[now].r)
		{
			if(b[now].l == b[now].r)
			{
				ans[b[now].id] = 0;
				now++;
				continue;
			}
			ans[b[now].id] = Segtree::segmax(1, b[now].l, b[now].r);
			now++;
		}
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
