#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n;
int minn[N], maxn[N];
int col[N];
struct SegTree
{
	int l, r;
	int sum, tag;
}tr[N << 3];
void pushup(int p)
{
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
}
void pushdown(int p)
{
	tr[p << 1].sum = tr[p << 1].r - tr[p << 1].l + 1;
	tr[p << 1 | 1].sum = tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1;
	tr[p << 1].tag = 1;
	tr[p << 1 | 1].tag = 1;
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].sum = tr[p].tag = 0;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void segchg(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		tr[p].sum = tr[p].r - tr[p].l + 1;
		tr[p].tag = 1;
		return;
	}
	if(tr[p].tag)pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)segchg(p << 1, l, r);
	if(r > mid)segchg(p << 1 | 1, l, r);
	pushup(p);
}
int segsum(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	if(tr[p].tag)pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	int res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
struct Data
{
	int col, pos;
};
stack<Data>sta;
void dump(stack<Data> &s)
{
	stack<Data>emp;
	swap(s, emp);
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%d", &col[i]);
	memset(minn, 0x3f, sizeof(minn));
	memset(maxn, 0, sizeof(maxn));
	build(1, 1, n);
	for(int i = 1; i <= n; i++)
	{
		minn[col[i]] = min(minn[col[i]], i);
		maxn[col[i]] = max(maxn[col[i]], i);
	}
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		if(i == maxn[col[i]] && maxn[col[i]] != minn[col[i]])
			segchg(1, minn[col[i]] + 1, maxn[col[i]]);
		else sta.push({ col[i],i });
		while(!sta.empty() && maxn[sta.top().col] <= i)sta.pop();
		int l = (sta.empty()) ? 0 : sta.top().pos;
		if(i != l)res += i - l - segsum(1, l + 1, i);
	}
	printf("%lld\n", res);
	dump(sta);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}