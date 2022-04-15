#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
struct SegTree
{
	int l, r;
	int sum;
}tr[N << 3];
int a[N];

void pushup(int p)
{
	tr[p].sum = min(tr[p << 1].sum, tr[p << 1 | 1].sum);
}
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if(l == r)
	{
		tr[p].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
int segmin(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	int res = 1000010;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = min(res, segmin(p << 1, l, r));
	if(r > mid)res = min(res, segmin(p << 1 | 1, l, r));
	return res;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(1, 1, n);
	while(m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d ", segmin(1, x, y));
	}
	return 0;
}
