#include<bits/stdc++.h>
#define ll long long
#define lson (p << 1)
#define rson (p << 1 | 1)
using namespace std;
const int MAXN = 1000010;
int n, cnt = 0;
ll lf, rt, tp, bt, X[MAXN << 1];
struct ScanLine
{
	ll l, r, h;
	int mark;
	bool operator < (const ScanLine &rhs) const
	{
		return h < rhs.h;
	}
} line[MAXN << 1];

struct SegTree
{
	int l, r, sum;
	ll len;
} tr[MAXN << 2];

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].len = 0;
	tr[p].sum = 0;
	if(l == r)
		return;
	int mid = (l + r) >> 1;
	build(lson, l, mid);
	build(rson, mid + 1, r);
	return;
}

void pushup(int p)
{
	int l = tr[p].l, r = tr[p].r;
	if(tr[p].sum)
		tr[p].len = X[r + 1] - X[l];
	else
		tr[p].len = tr[lson].len + tr[rson].len;
}

void segadd(int p, ll L, ll R, int c)
{
	int l = tr[p].l, r = tr[p].r;
	if(X[r + 1] <= L || R <= X[l])
		return;
	if(L <= X[l] && X[r + 1] <= R)
	{
		tr[p].sum += c;
		pushup(p);
		return;
	}
	segadd(lson, L, R, c);
	segadd(rson, L, R, c);
	pushup(p);
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld%lld", &lf, &bt, &rt, &tp);
		if(lf > rt)swap(lf, rt);
		if(bt > tp)swap(bt, tp);
		if(lf == rt)lf--, rt++;
		else if(bt == tp)bt--, tp++;
		X[2 * i - 1] = lf;
		X[2 * i] = rt;
		line[2 * i - 1] = { lf, rt, bt, 1 };
		line[2 * i] = { lf, rt, tp, -1 };
	}
	n <<= 1;
	sort(line + 1, line + n + 1);
	sort(X + 1, X + n + 1);
	int tot = unique(X + 1, X + n + 1) - X - 1;
	build(1, 1, tot - 1);
	ll ans = 0;
	for(int i = 1; i < n; i++)
	{
		segadd(1, line[i].l, line[i].r, line[i].mark);
		ans += tr[1].len * (line[i + 1].h - line[i].h);
	}
	printf("%lld", ans);
	return 0;
}