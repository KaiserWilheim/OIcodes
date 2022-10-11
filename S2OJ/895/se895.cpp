#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N];
struct Query
{
	int l, r;
	int k, id;
	friend bool operator < (const Query &lhs, const Query &rhs)
	{
		return lhs.k < rhs.k;
	}
};
Query q[N];
struct Node
{
	int l, r;
	int ls, rs;
	int sum;
};
Node tr[N << 5];
int rt[N], idx;
int build(int l, int r)
{
	int p = ++idx;
	tr[p].l = l, tr[p].r = r;
	if(l == r)return p;
	int mid = (tr[p].l + tr[p].r) >> 1;
	tr[p].ls = build(l, mid);
	tr[p].rs = build(mid + 1, r);
	return p;
}
int insert(int p, int pos)
{
	int q = ++idx;
	tr[q] = tr[p];
	tr[q].sum++;
	if(tr[q].l == tr[q].r)return q;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)tr[q].ls = insert(tr[p].ls, pos);
	if(pos > mid)tr[q].rs = insert(tr[p].rs, pos);
	return q;
}
int segsum(int p, int q)
{
	if(tr[p].sum == tr[q].sum)return 0;
	if(tr[p].l == tr[p].r)return tr[p].l;
	int res = tr[tr[q].rs].sum - tr[tr[p].rs].sum;
	if(res)return segsum(tr[p].rs, tr[q].rs);
	else return segsum(tr[p].ls, tr[q].ls);
}
int segmax(int p, int q, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return segsum(p, q);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res = max(res, segmax(tr[p].ls, tr[q].ls, l, r));
	if(r > mid)res = max(res, segmax(tr[p].rs, tr[q].rs, l, r));
	return res;
}
int S, cnt;
int bl[N], L[N], R[N], b[N], c[N];
int ans[N];
void init()
{
	S = sqrt(n), cnt = n / S;
	if(n % S)cnt++;
	for(int i = 1; i <= n; i++)bl[i] = (i - 1) / S + 1;
	for(int i = 1; i <= cnt; i++)L[i] = R[i - 1] + 1, R[i] = i * S;
	R[cnt] = n;
}
void rbuild(int k)
{
	for(int i = 1; i <= n; i++)b[i] = a[i] % k;
	for(int i = 1; i <= cnt; i++)
	{
		c[i] = 0;
		for(int j = L[i]; j <= R[i]; j++)
			c[i] = max(c[i], b[j]);
	}
}
int calc(int l, int r)
{
	int res = 0;
	if(bl[l] == bl[r])
	{
		for(int i = l; i <= r; i++)
			res = max(res, b[i]);
		return res;
	}
	for(int i = l; i <= R[bl[l]]; i++)res = max(res, b[i]);
	for(int i = bl[l] + 1; i < bl[r]; i++)res = max(res, c[i]);
	for(int i = L[bl[r]]; i <= r; i++)res = max(res, b[i]);
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	init();
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		maxn = max(maxn, a[i]);
	}
	rt[0] = build(0, maxn);
	for(int i = 1; i <= n; i++)
		rt[i] = insert(rt[i - 1], a[i]);
	for(int i = 1; i <= m; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		q[i] = { l,r,k,i };
	}
	sort(q + 1, q + 1 + m);
	int pos = m;
	for(int i = 1; i <= m; i++)
	{
		if(q[i].k > 2000)
		{
			pos = i;
			break;
		}
		if(q[i].k != q[i - 1].k)rbuild(q[i].k);
		ans[q[i].id] = calc(q[i].l, q[i].r);
	}
	for(int i = pos; i <= m; i++)
	{
		int res = 0, t = 1;
		int l = q[i].l, r = q[i].r, k = q[i].k;
		while(t * k - 1 <= maxn)
		{
			res = max(res, segmax(rt[l - 1], rt[r], (t - 1) * k, t * k - 1) % k);
			t++;
		}
		if(t * k - 1 > maxn)res = max(res, segmax(rt[l - 1], rt[r], (t - 1) * k, maxn) % k);
		ans[q[i].id] = res;
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}