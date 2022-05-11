#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
double a[N];
struct SegTree
{
	double max;
	int len;
}tr[N << 3];
void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
}
int update(double k, int p, int l, int r)
{
	if(tr[p].max <= k)return 0;
	if(a[l] > k)return tr[p].len;
	if(l == r)return a[l] > k;
	int mid = (l + r) >> 1;
	if(tr[p << 1].max <= k)return update(k, p << 1 | 1, mid + 1, r);
	else return update(k, p << 1, l, mid) + tr[p].len - tr[p << 1].len;
}
void segadd(int p, int l, int r, int pos, int k)
{
	if(l == r)
	{
		tr[p].max = ( double )k / pos;
		tr[p].len = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)segadd(p << 1, l, mid, pos, k);
	else segadd(p << 1 | 1, mid + 1, r, pos, k);
	pushup(p);
	tr[p].len = tr[p << 1].len + update(tr[p << 1].max, p << 1 | 1, mid + 1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		a[x] = ( double )y / x;
		segadd(1, 1, n, x, y);
		printf("%d\n", tr[1].len);
	}
	return 0;
}
