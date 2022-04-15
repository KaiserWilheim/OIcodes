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
	tr[p].sum = max(tr[p << 1].sum, tr[p << 1 | 1].sum);
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
void segadd(int p, int pos, int k)
{
	if(tr[p].l == tr[p].r)
	{
		tr[p].sum = k;
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(pos <= mid)segadd(p << 1, pos, k);
	if(pos > mid)segadd(p << 1 | 1, pos, k);
	pushup(p);
}
int segmax(int p, int l, int r)
{
	if(tr[p].l >= l && tr[p].r <= r)return tr[p].sum;
	int res = 0;
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}

int p, t, len;
int main()
{
	int n, m;
	scanf("%d%d", &m, &p);
	n = 200010;
	build(1, 1, n);
	while(m--)
	{
		string op;
		int x;
		cin >> op >> x;
		if(op[0] == 'Q')
		{
			t = segmax(1, len - x + 1, len);
			cout << t << endl;
		}
		else if(op[0] == 'A')
		{
			segadd(1, ++len, (x + t) % p);
		}
	}
	return 0;
}
