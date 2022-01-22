#include<bits/stdc++.h>
#define lson (x << 1)
#define rson (x << 1 | 1)
using namespace std;
const int MAXN = 1000010;
int n, cnt = 0;
long long lf, rt, tp, bt, X[MAXN << 1];
struct ScanLine
{
	long long l, r, h;
	int mark;
	bool operator < (const ScanLine &rhs) const
	{
		return h < rhs.h;
	}
} line[MAXN << 1];

struct SegTree
{
	int l, r, sum;
	long long len;
} tree[MAXN << 2];

void build_tree(int x, int l, int r)
{
	tree[x].l = l, tree[x].r = r;
	tree[x].len = 0;
	tree[x].sum = 0;
	if(l == r)
		return;
	int mid = (l + r) >> 1;
	build_tree(lson, l, mid);
	build_tree(rson, mid + 1, r);
	return;
}

void pushup(int x)
{
	int l = tree[x].l, r = tree[x].r;
	if(tree[x].sum)
		tree[x].len = X[r + 1] - X[l];
	else
		tree[x].len = tree[lson].len + tree[rson].len;
}

void edit_tree(int x, long long L, long long R, int c)
{
	int l = tree[x].l, r = tree[x].r;
	if(X[r + 1] <= L || R <= X[l])
		return;
	if(L <= X[l] && X[r + 1] <= R)
	{
		tree[x].sum += c;
		pushup(x);
		return;
	}
	edit_tree(lson, L, R, c);
	edit_tree(rson, L, R, c);
	pushup(x);
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld%lld", &lf, &bt, &rt, &tp);
		X[2 * i - 1] = lf;
		X[2 * i] = rt;
		line[2 * i - 1] = { lf, rt, bt, 1 };
		line[2 * i] = { lf, rt, tp, -1 };
	}
	n <<= 1;
	sort(line + 1, line + n + 1);
	sort(X + 1, X + n + 1);
	int tot = unique(X + 1, X + n + 1) - X - 1;
	build_tree(1, 1, tot - 1);
	long long ans = 0;
	for(int i = 1; i < n; i++)
	{
		edit_tree(1, line[i].l, line[i].r, line[i].mark);
		ans += tree[1].len * (line[i + 1].h - line[i].h);
	}
	printf("%lld", ans);
	return 0;
}
