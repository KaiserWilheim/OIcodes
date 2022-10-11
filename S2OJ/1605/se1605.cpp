#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010;
int n, m;
struct Query
{
	int l, r, v;
	bool operator < (const Query &rhs)const
	{
		return r < rhs.r;
	}
};
namespace SegTree
{
	struct Node
	{
		int l, r;
		int maxn;
	};
	Node tr[N << 3];
	void pushup(int p)
	{
		tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
	}
	void build(int p, int l, int r)
	{
		tr[p].l = l, tr[p].r = r;
		tr[p].maxn = 0;
		if(l == r)return;
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
	}
	void segadd(int p, int pos, int k)
	{
		if(tr[p].l == tr[p].r)
		{
			tr[p].maxn = max(tr[p].maxn, k);
			return;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(pos <= mid)segadd(p << 1, pos, k);
		if(pos > mid)segadd(p << 1 | 1, pos, k);
		pushup(p);
	}
	int segsum(int p, int l, int r)
	{
		if(tr[p].l >= l && tr[p].r <= r)return tr[p].maxn;
		int mid = (tr[p].l + tr[p].r) >> 1;
		int res = 0;
		if(l <= mid)res = max(res, segsum(p << 1, l, r));
		if(r > mid)res = max(res, segsum(p << 1 | 1, l, r));
		return res;
	}
}
namespace LCTree
{
	struct Line
	{
		int k, b;
		Line() { k = b = 0; }
		Line(int _k, int _b) { k = _k, b = _b; }
		bool empty()
		{
			return k == 0 && b == 0;
		}
	};
	struct Node
	{
		int ls, rs;
		Line s;
		void clear()
		{
			ls = rs = 0;
			s = { 0,0 };
		}
	};
	Node tr[N << 4];
	int idx = 0;
	int rt[N];
	int getval(Line p, int x)
	{
		return p.k * x + p.b;
	}
	void insert(int &p, int l, int r, Line k)
	{
		if(!p)p = ++idx;
		if(tr[p].s.empty())
		{
			tr[p].s = k;
			return;
		}
		if(l == r)return;
		int mid = (l + r) >> 1;
		int pre = getval(tr[p].s, mid), now = getval(k, mid);
		if(now > pre)swap(tr[p].s, k), swap(now, pre);
		if(getval(tr[p].s, l) < getval(k, l))insert(tr[p].ls, l, mid, k);
		else insert(tr[p].rs, mid + 1, r, k);
	}
	int segqry(int p, int l, int r, int x)
	{
		if(!p)return 0;
		int mid = (l + r) >> 1;
		int res = getval(tr[p].s, x);
		if(x <= mid)res = max(res, segqry(tr[p].ls, l, mid, x));
		else res = max(res, segqry(tr[p].rs, mid + 1, r, x));
		return res;
	}
	#define lowbit(x) (x&(-x))
	void segadd(int x, Line k)
	{
		for(int i = x; i <= 1e5; i += lowbit(i))
			insert(rt[i], 1, 1e5, k);
	}
	int segsum(int x, int k)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res = max(res, segqry(rt[i], 1, 1e5, k));
		return res;
	}
	void clear()
	{
		memset(rt, 0, sizeof(rt));
		for(int i = 1; i <= idx; i++)tr[i].clear();
		idx = 0;
	}
}
Query a[N], b[N];
int ans = 0;
void solve()
{
	for(int i = 1, j = 0; i <= n; i++)
	{
		while(j + 1 <= n && a[j + 1].r <= b[i].r)
		{
			j++;
			SegTree::segadd(1, a[j].l, (a[j].r - a[j].l + 1) * a[j].v);
			LCTree::segadd(a[j].l, { -a[j].v,(a[j].r + 1) * a[j].v });
		}
		ans = max(ans, SegTree::segsum(1, b[i].l, b[i].r) * b[i].v);
		ans = max(ans, LCTree::segsum(b[i].l, b[i].l) * b[i].v);
	}
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].v);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld%lld", &b[i].l, &b[i].r, &b[i].v);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	SegTree::build(1, 1, 1e5);
	solve();
	SegTree::build(1, 1, 1e5);
	LCTree::clear();
	for(int i = 1; i <= n; i++)swap(a[i], b[i]);
	solve();
	printf("%lld\n", ans);
	return 0;
}