#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 400010, M = N << 1;
const int INF = 1e9;
int n;
struct Node
{
	int id, l, r, k;
	Node() { id = l = r = k = 0; }
	Node(int _i, int _l, int _r, int _k) { id = _i, l = _l, r = _r, k = _k; }
};
Node a[N];
int bl[N], w[N];
int lh[N], rh[N];

namespace SEG
{
	struct SegTree
	{
		int ls, rs;
		int pos, minn, tag;
	};
	SegTree tr[N << 6];
	int idx;
	void pushup(int p)
	{
		if(tr[p].ls && tr[p].rs)
		{
			tr[p].minn = min(tr[tr[p].ls].minn, tr[tr[p].rs].minn);
			if(tr[p].minn == tr[tr[p].ls].minn)tr[p].pos = tr[tr[p].ls].pos;
			else tr[p].pos = tr[tr[p].rs].pos;
		}
		else if(tr[p].ls)
		{
			tr[p].minn = tr[tr[p].ls].minn;
			tr[p].pos = tr[tr[p].ls].pos;
		}
		else if(tr[p].rs)
		{
			tr[p].minn = tr[tr[p].rs].minn;
			tr[p].pos = tr[tr[p].rs].pos;
		}
	}
	void pushdown(int p)
	{
		if(tr[p].ls)
		{
			tr[tr[p].ls].minn += tr[p].tag;
			tr[tr[p].ls].tag += tr[p].tag;
		}
		if(tr[p].rs)
		{
			tr[tr[p].rs].minn += tr[p].tag;
			tr[tr[p].rs].tag += tr[p].tag;
		}
		tr[p].tag = 0;
	}
	void build(int &p, int l, int r)
	{
		if(l > r)return;
		if(!p)p = ++idx;
		if(l == r)
		{
			tr[p].minn = w[l];
			tr[p].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(tr[p].ls, l, mid);
		build(tr[p].rs, mid + 1, r);
		pushup(p);
	}
	void segchg(int &p, int l, int r, int pos, int k)
	{
		if(l > r)return;
		if(!p)p = ++idx;
		if(l == r)
		{
			tr[p].minn = k;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (l + r) >> 1;
		if(pos <= mid)segchg(tr[p].ls, l, mid, pos, k);
		else segchg(tr[p].rs, mid + 1, r, pos, k);
		pushup(p);
	}
	void segsub(int &p, int l, int r, int ql, int qr)
	{
		if(l > r)return;
		if(!p)p = ++idx;
		if(ql <= l && r <= qr)
		{
			tr[p].tag--;
			tr[p].minn--;
			return;
		}
		if(tr[p].tag)pushdown(p);
		int mid = (l + r) >> 1;
		if(ql <= mid)segsub(tr[p].ls, l, mid, ql, qr);
		if(qr > mid)segsub(tr[p].rs, mid + 1, r, ql, qr);
		pushup(p);
	}
	int segmin(int &p, int l, int r, int ql, int qr)
	{
		if(l > r)return INF;
		if(ql <= l && r <= qr)return tr[p].minn;
		if(tr[p].tag)pushdown(p);
		int mid = (l + r) >> 1;
		int res = INF;
		if(ql <= mid)res = min(res, segmin(tr[p].ls, l, mid, ql, qr));
		if(qr > mid)res = min(res, segmin(tr[p].rs, mid + 1, r, ql, qr));
		return res;
	}
}

queue<int>q;
bool vis[N];

namespace DIV
{
	bool cmp1(Node lhs, Node rhs)
	{
		return lhs.l == rhs.l ? lhs.r < rhs.r : lhs.l < rhs.l;
	}
	bool cmp2(Node lhs, Node rhs)
	{
		return lhs.r == rhs.r ? lhs.l < rhs.l : lhs.r < rhs.r;
	}
	struct Div
	{
		int pl, pr;
		vector<Node>al, ar;
		vector<int>kl, kr;
	};
	Div tr[N << 3];
	int rt[N << 3];
	int tot;
	void build(int p, int l, int r, vector<Node>tmp)
	{
		tr[p].pl = ++tot, tr[p].pr = ++tot;
		int mid = (l + r) >> 1;
		vector<Node>tmpl, tmpr;
		for(auto i : tmp)
		{
			if(i.l <= mid && i.r >= mid)
			{
				tr[p].al.push_back(i), tr[p].ar.push_back(i);
				tr[p].kl.push_back(i.l), tr[p].kr.push_back(i.r);
				bl[i.id] = p;
			}
			else if(i.r < mid)tmpl.push_back(i);
			else if(i.l > mid)tmpr.push_back(i);
		}

		sort(tr[p].al.begin(), tr[p].al.end(), cmp1);
		sort(tr[p].kl.begin(), tr[p].kl.end());
		for(int i = 0; i < tr[p].al.size(); i++)
			w[i] = tr[p].al[i].k / 2, lh[tr[p].al[i].id] = i;
		SEG::build(rt[tr[p].pl], 0, tr[p].al.size() - 1);

		sort(tr[p].ar.begin(), tr[p].ar.end(), cmp2);
		sort(tr[p].kr.begin(), tr[p].kr.end());
		for(int i = 0; i < tr[p].ar.size(); i++)
			w[i] = tr[p].ar[i].k - tr[p].ar[i].k / 2, rh[tr[p].ar[i].id] = i;
		SEG::build(rt[tr[p].pr], 0, tr[p].ar.size() - 1);

		if(l == r)return;
		build(p << 1, l, mid, tmpl);
		build(p << 1 | 1, mid + 1, r, tmpr);
	}
	void chq(int p)
	{
		if(tr[p].al.empty())return;
		int sz = tr[p].al.size() - 1;
		while(SEG::tr[rt[tr[p].pl]].minn <= 0)
		{
			int pos = SEG::tr[rt[tr[p].pl]].pos,
				pos1 = rh[tr[p].al[pos].id],
				id = tr[p].al[pos].id;
			int num1 = SEG::segmin(rt[tr[p].pl], 0, sz, pos, pos),
				num2 = SEG::segmin(rt[tr[p].pr], 0, sz, pos1, pos1);
			int num = num1 + num2;
			if(num <= 0)
			{
				q.push(id);
				SEG::segchg(rt[tr[p].pl], 0, sz, pos, INF);
				SEG::segchg(rt[tr[p].pr], 0, sz, pos1, INF);
			}
			else
			{
				int nr = num / 2, nl = num - nr;
				SEG::segchg(rt[tr[p].pl], 0, sz, pos, nl);
				SEG::segchg(rt[tr[p].pr], 0, sz, pos1, nr);
			}
		}
		while(SEG::tr[rt[tr[p].pr]].minn <= 0)
		{
			int pos1 = SEG::tr[rt[tr[p].pr]].pos,
				pos = lh[tr[p].ar[pos1].id],
				id = tr[p].al[pos].id;
			int num1 = SEG::segmin(rt[tr[p].pl], 0, sz, pos, pos),
				num2 = SEG::segmin(rt[tr[p].pr], 0, sz, pos1, pos1);
			int num = num1 + num2;
			if(num <= 0)
			{
				q.push(id);
				SEG::segchg(rt[tr[p].pl], 0, sz, pos, INF);
				SEG::segchg(rt[tr[p].pr], 0, sz, pos1, INF);
			}
			else
			{
				int nr = num / 2, nl = num - nr;
				SEG::segchg(rt[tr[p].pl], 0, sz, pos, nr);
				SEG::segchg(rt[tr[p].pr], 0, sz, pos1, nl);
			}
		}
	}
	void segdel(int p, int l, int r, int x)
	{
		int mid = (l + r) >> 1;
		int sz = tr[p].al.size() - 1;
		if(x <= mid)
		{
			int pos = upper_bound(tr[p].kl.begin(), tr[p].kl.end(), x) - tr[p].kl.begin();
			if(pos)SEG::segsub(rt[tr[p].pl], 0, sz, 0, pos - 1);
		}
		else
		{
			int pos = lower_bound(tr[p].kr.begin(), tr[p].kr.end(), x) - tr[p].kr.begin();
			if(pos <= sz)SEG::segsub(rt[tr[p].pr], 0, sz, pos, sz);
		}
		chq(p);
		if(l == r)return;
		if(x <= mid)segdel(p << 1, l, mid, x);
		else segdel(p << 1 | 1, mid + 1, r, x);
	}
}

int main()
{
	scanf("%d", &n);
	vector<Node>tmp;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].k);
		a[i].id = i;
		tmp.push_back(a[i]);
	}
	DIV::build(1, 1, n, tmp);
	for(int i = 1; i <= n; i++)
		if(!a[i].k)
			q.push(i);
	int ans = 0;
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		if(vis[now])continue;
		vis[now] = true;
		ans++;
		DIV::segdel(1, 1, n, now);
	}
	printf("%d\n", ans);
	return 0;
}
