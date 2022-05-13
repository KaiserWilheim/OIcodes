#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
int n, m;
struct SegTree
{
	int l, r;
	int max, tag;
}tr[N << 4];
void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
}
void pushdown(int p)
{
	if(tr[p].tag)
	{
		auto &root = tr[p], &left = tr[p << 1], &rght = tr[p << 1 | 1];
		left.tag += root.tag;
		left.max += root.tag;
		rght.tag += root.tag;
		rght.max += root.tag;
		root.tag = 0;
	}
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].max = tr[p].tag = 0;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void segadd(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].max += k;
		tr[p].tag += k;
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segadd(p << 1, l, r, k);
	if(r > mid)segadd(p << 1 | 1, l, r, k);
	pushup(p);
}

struct query
{
	int l, r;
	int len;
	bool operator < (const query &a)const
	{
		return len < a.len;
	}
}a[N];
int x[N << 1], idx;
map<int, int>dic;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].l, &a[i].r);
		a[i].len = a[i].r - a[i].l;
		x[i * 2 - 2] = a[i].l, x[i * 2 - 1] = a[i].r;
	}
	sort(x, x + 2 * n);
	idx = unique(x, x + 2 * n) - x;
	for(int i = 0; i < idx; i++)
		dic.insert(make_pair(x[i], i + 1));
	sort(a + 1, a + 1 + n);
	build(1, 1, idx);
	int hh = 0;
	int ans = 0x3f3f3f3f;
	for(int i = 1; i <= n; i++)
	{
		int l = dic[a[i].l], r = dic[a[i].r];
		segadd(1, l, r, 1);
		if(tr[1].max >= m)
		{
			while(tr[1].max >= m && hh <= n)
			{
				hh++;
				int hl = dic[a[hh].l], hr = dic[a[hh].r];
				segadd(1, hl, hr, -1);
			}
			ans = min(ans, a[i].len - a[hh].len);
		}
	}
	if(ans == 0x3f3f3f3f)puts("-1");
	else printf("%d\n", ans);
	return 0;
}
