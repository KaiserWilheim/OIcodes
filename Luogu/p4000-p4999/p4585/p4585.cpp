#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
struct Trie
{
	struct Node
	{
		int s[2], w;
	};
	Node tr[N << 5];
	int rt[N], idx;
	void insert(int &p, int q, int w, int now)
	{
		p = ++idx;
		tr[p] = tr[q];
		tr[p].w++;
		if(now == -1)return;
		bool c = (w >> now) & 1;
		insert(tr[p].s[c], tr[q].s[c], w, now - 1);
	}
	int query(int l, int r, int w, int now)
	{
		if(now == -1)return 0;
		bool c = (w >> now) & 1;
		int tmp = tr[tr[r].s[c ^ 1]].w - tr[tr[l].s[c ^ 1]].w;
		if(tmp)return query(tr[l].s[c ^ 1], tr[r].s[c ^ 1], w, now - 1) + (1 << now);
		else return query(tr[l].s[c], tr[r].s[c], w, now - 1);
	}
};
Trie trie;
int ans[N];
vector<int>tr[N << 3];
void segchg(int p, int l, int r, int ql, int qr, int k)
{
	if(ql > qr)return;
	if(l >= ql && r <= qr)
	{
		tr[p].push_back(k);
		return;
	}
	int mid = (l + r) >> 1;
	if(ql <= mid)segchg(p << 1, l, mid, ql, qr, k);
	if(qr > mid)segchg(p << 1 | 1, mid + 1, r, ql, qr, k);
}
int sta[N], tt;
int bin(int x)
{
	int l = 1, r = tt;
	int res = 0;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(sta[mid] <= x)res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}
struct Buy
{
	int s, v, t;
	bool operator < (const Buy &rhs)const
	{
		return s < rhs.s;
	}
};
Buy q[N], q1[N], q2[N];
struct Query
{
	int l, r, tl, tr, x;
};
Query qry[N];
void calc(int p, int l, int r)
{
	tt = trie.idx = 0;
	for(int i = l; i <= r; i++)
	{
		sta[++tt] = q[i].s;
		trie.insert(trie.rt[tt], trie.rt[tt - 1], q[i].v, 17);
	}
	for(int i = 0; i < tr[p].size(); i++)
	{
		int k = tr[p][i];
		int l = bin(qry[k].l - 1), r = bin(qry[k].r);
		ans[k] = max(ans[k], trie.query(trie.rt[l], trie.rt[r], qry[k].x, 17));
	}
}
void divide(int p, int l, int r, int ql, int qr)
{
	if(ql > qr)return;
	int mid = (l + r) >> 1;
	int tt1 = 0, tt2 = 0;
	calc(p, ql, qr);
	if(l == r)return;
	for(int i = ql; i <= qr; i++)
	{
		if(q[i].t <= mid)q1[++tt1] = q[i];
		else q2[++tt2] = q[i];
	}
	for(int i = 1; i <= tt1; i++)q[i + ql - 1] = q1[i];
	for(int i = 1; i <= tt2; i++)q[i + ql + tt1 - 1] = q2[i];
	divide(p << 1, l, mid, ql, ql + tt1 - 1);
	divide(p << 1 | 1, mid + 1, r, ql + tt1, qr);
}
int cnt1, cnt2;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int w;
		scanf("%d", &w);
		trie.insert(trie.rt[i], trie.rt[i - 1], w, 17);
	}
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if(!op)
		{
			int s, v;
			scanf("%d%d", &s, &v);
			cnt1++;
			q[cnt1] = { s,v,cnt1 };
		}
		else
		{
			int l, r, x, d;
			scanf("%d%d%d%d", &l, &r, &x, &d);
			ans[++cnt2] = trie.query(trie.rt[l - 1], trie.rt[r], x, 17);
			qry[cnt2] = { l,r,max(1,cnt1 - d + 1),cnt1,x };
		}
	}
	for(int i = 1; i <= cnt2; i++)
		segchg(1, 1, cnt1, qry[i].tl, qry[i].tr, i);
	sort(q + 1, q + 1 + cnt1);
	divide(1, 1, cnt1, 1, cnt1);
	for(int i = 1; i <= cnt2; i++)
		printf("%d\n", ans[i]);
	return 0;
}
