#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010, M = N << 1;
const int INF = 1e9;
struct Node
{
	int u, dis;
	bool operator < (const Node &rhs)const { return dis < rhs.dis; }
};
struct Point
{
	int x, y, op;
	Point() {}
	Point(int _x, int _y, int _op) { x = _x, y = _y, op = _op; }
	bool operator < (const Point &rhs)const { return x < rhs.x; }
};
struct Query
{
	int x, y, id;
	bool operator < (const Query &rhs)const { return x < rhs.x; }
};
struct Line
{
	int x, t, b, op;
	Line() {}
	Line(int _x, int _t, int _b, int _op)
	{
		x = _x, t = _t, b = _b, op = _op;
	}
	bool operator < (const Line &rhs)const
	{
		if(x != rhs.x)return x < rhs.x;
		return op > rhs.op;
	}
};
struct SegTree
{
	struct Node
	{
		int sum, add;
		bool tag;
	};
	Node tr[N << 3];
	void pushup(int p)
	{
		tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
		tr[p].tag = tr[p].sum > 0 ? 0 : 1;
	}
	void pushdown(int p, int l, int r)
	{
		if(tr[p].add != 0)
		{
			int mid = (l + r) >> 1;
			tr[p << 1].sum += tr[p].add * (mid - l + 1);
			tr[p << 1 | 1].sum += tr[p].add * (r - mid);
			tr[p << 1].add += tr[p].add;
			tr[p << 1 | 1].add += tr[p].add;
			tr[p].add = 0;
		}
		tr[p << 1].tag = tr[p << 1].sum > 0 ? 0 : 1;
		tr[p << 1 | 1].tag = tr[p << 1 | 1].sum > 0 ? 0 : 1;
	}
	void segadd(int p, int l, int r, int ql, int qr, int k)
	{
		if(ql <= l && r <= qr)
		{
			tr[p].sum += k * (r - l + 1);
			tr[p].add += k;
			tr[p].tag = tr[p].sum > 0 ? 0 : 1;
			return;
		}
		pushdown(p, l, r);
		int mid = (l + r) >> 1;
		if(ql <= mid)segadd(p << 1, l, mid, ql, qr, k);
		if(qr > mid)segadd(p << 1 | 1, mid + 1, r, ql, qr, k);
		pushup(p);
	}
	int pos;
	void segqry(int p, int l, int r)
	{
		tr[p].tag = tr[p].sum > 0 ? 0 : 1;
		if(tr[p].tag)
		{
			pos = max(pos, r + 1);
			return;
		}
		if(l == r)return;
		pushdown(p, l, r);
		int mid = (l + r) >> 1;
		if(!tr[p << 1].tag)segqry(p << 1, l, mid);
		else
		{
			pos = max(pos, mid + 1);
			segqry(p << 1 | 1, mid + 1, r);
		}
	}
};
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
SegTree tr;
struct BIT
{
#define lowbit(i) (i&-i)
	int tr[N];
	void add(int x, int c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr[i] += c;
	}
	int sum(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
};
BIT bit;
int fa[N], son[N], sz[N], top[N];
Node a[N];
void dfs1(int p, int fa, int dep)
{
	::fa[p] = fa, sz[p] = 1;
	a[p] = { p,dep };
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p, dep + w[i]);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
set<int>s;
vector<pair<int, int>>v[N];
void instree(int p)
{
	s.insert(p);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p])continue;
		instree(e[i]);
	}
}
void deltree(int p)
{
	s.erase(p);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p])continue;
		deltree(e[i]);
	}
}
void addtree(int p, int id)
{
	s.insert(p);
	auto t1 = s.lower_bound(p), t2 = s.lower_bound(p);
	if(t1 != s.begin())v[id].emplace_back(*prev(t1), p);
	if(t2 != prev(s.end()))v[id].emplace_back(p, *next(t2));
	s.erase(p);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p])continue;
		addtree(e[i], id);
	}
}
void dfs2(int p)
{
	v[p].emplace_back(p, p);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i]);
		deltree(e[i]);
	}
	if(!son[p])
	{
		s.insert(p);
		return;
	}
	dfs2(son[p]);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		addtree(e[i], p);
		instree(e[i]);
	}
	s.insert(p);
}
Line line[M];
int tt;
Point point[M];
int ptt;
void scan()
{
	sort(line + 1, line + 1 + tt);
	int now = 1; tr.pos = INF;
	while(now <= tt && line[now].op == 1)
	{
		tr.segadd(1, 1, n, line[now].t, line[now].b, line[now].op);
		tr.pos = min(tr.pos, line[now].t);
		now++;
	}
	int lst = 1;
	while(now <= tt)
	{
		point[++ptt] = Point(line[now].x + 1, tr.pos, -1);
		point[++ptt] = Point(lst, tr.pos, 1);
		tr.segadd(1, 1, n, line[now].t, line[now].b, line[now].op);
		tr.segqry(1, 1, n);
		lst = line[now].x + 1;
		now++;
	}
}
Query q[N];
int ans[N];
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	dfs1(1, 0, 0);
	sort(a + 1, a + 1 + n);
	dfs2(1);
	for(int i = 1; i <= n; i++)
	{
		tt = 0;
		int j = i;
		while(a[j].dis == a[j + 1].dis && j < n)j++;
		for(int k = i; k <= j; k++)
		{
			for(auto it : v[a[k].u])
			{
				line[++tt] = Line(1, it.second, n, 1);
				line[++tt] = Line(it.first, it.second, n, -1);
			}
		}
		i = j;
		if(tt)scan();
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%lld%lld", &q[i].x, &q[i].y);
		q[i].id = i;
	}
	sort(q + 1, q + 1 + m);
	sort(point + 1, point + 1 + ptt);
	int now = 1;
	for(int i = 1; i <= m; i++)
	{
		while(now <= ptt && point[now].x <= q[i].x)
		{
			bit.add(point[now].y, point[now].op);
			now++;
		}
		ans[q[i].id] = bit.sum(q[i].y);
	}
	for(int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
