#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;
int n, m;
struct ChmTree
{
	struct Node
	{
		int l, r;
		int ls, rs;
		int tag;
	};
	Node tr[N * 64];
	int root[N];
	int idx = 0;
	int build(int l, int r)
	{
		int p = ++idx;
		tr[p] = { l,r,0,0,0 };
		if(l == r)return p;
		int mid = (l + r) >> 1;
		tr[p].ls = build(l, mid);
		tr[p].rs = build(mid + 1, r);
		return p;
	}
	int segadd(int p, int l, int r, int k)
	{
		int q = ++idx;
		tr[q] = tr[p];
		if(tr[p].l >= l && tr[p].r <= r)
		{
			tr[q].tag += k;
			return q;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(l <= mid)tr[q].ls = segadd(tr[p].ls, l, r, k);
		if(r > mid)tr[q].rs = segadd(tr[p].rs, l, r, k);
		return q;
	}
	int segsum(int p, int pos)
	{
		if(tr[p].l == tr[p].r)return tr[p].tag;
		int mid = (tr[p].l + tr[p].r) >> 1;
		if(pos <= mid)return segsum(tr[p].ls, pos) + tr[p].tag;
		if(pos > mid)return segsum(tr[p].rs, pos) + tr[p].tag;
	}
};
ChmTree col;
pair<int, int> row[N];
signed main()
{
	int q;
	scanf("%lld%lld%lld", &n, &m, &q);
	col.root[0] = col.build(1, m);
	for(int i = 1; i <= q; i++)
	{
		int op, l, r, k;
		scanf("%lld%lld%lld", &op, &l, &r);
		if(op == 1)
		{
			scanf("%lld", &k);
			col.root[i] = col.segadd(col.root[i - 1], l, r, k);
		}
		else if(op == 2)
		{
			row[l] = make_pair(r, i);
			col.root[i] = col.root[i - 1];
		}
		else
		{
			col.root[i] = col.root[i - 1];
			int sum = col.segsum(col.root[i], r);
			sum -= col.segsum(col.root[row[l].second], r);
			sum += row[l].first;
			printf("%lld\n", sum);
		}
	}
	return 0;
}