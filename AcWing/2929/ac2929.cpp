#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c != '-' && !(c >= '0' && c <= '9'))c = getchar();
	if(c == '-')f = -1, c = getchar();
	while(c >= '0' && c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return f * x;
}
int n, m;
int q;
int a[N];
int L[N << 3], R[N << 3], v[N << 3], t[N << 3];
inline void pushdown(int p)
{
	v[p << 1] = (R[p << 1] - L[p << 1] + 1) * t[p];
	v[p << 1 | 1] = (R[p << 1 | 1] - L[p << 1 | 1] + 1) * t[p];
	t[p << 1] = t[p];
	t[p << 1 | 1] = t[p];
	t[p] = -1;
}
inline void build(int p, int l, int r)
{
	L[p] = l, R[p] = r;
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
inline void init(int p, int k)
{
	t[p] = -1;
	if(L[p] == R[p])
	{
		v[p] = (a[L[p]] >= k);
		t[p] = -1;
		return;
	}
	init(p << 1, k);
	init(p << 1 | 1, k);
	v[p] = v[p << 1] + v[p << 1 | 1];
}
inline void segchg(int p, int l, int r, int k)
{
	if(L[p] >= l && R[p] <= r)
	{
		v[p] = (R[p] - L[p] + 1) * k;
		t[p] = k;
		return;
	}
	if(t[p] != -1)pushdown(p);
	int mid = (L[p] + R[p]) >> 1;
	if(l <= mid)segchg(p << 1, l, r, k);
	if(r > mid)segchg(p << 1 | 1, l, r, k);
	v[p] = v[p << 1] + v[p << 1 | 1];
}
inline int segsum(int p, int l, int r)
{
	if(L[p] >= l && R[p] <= r)return v[p];
	if(t[p] != -1)pushdown(p);
	int mid = (L[p] + R[p]) >> 1;
	int res = 0;
	if(l <= mid)res += segsum(p << 1, l, r);
	if(r > mid)res += segsum(p << 1 | 1, l, r);
	return res;
}
int op[N], ql[N], qr[N];
int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i <= m; i++)
		op[i] = read(), ql[i] = read(), qr[i] = read();
	q = read();
	build(1, 1, n);
	int ans = -1;
	int left = 1, rght = n;
	while(left <= rght)
	{
		int mid = (left + rght) >> 1;
		init(1, mid);
		for(int i = 1; i <= m; i++)
		{
			int cnt = segsum(1, ql[i], qr[i]);
			if(op[i] == 0)
			{
				segchg(1, ql[i], qr[i] - cnt, 0);
				segchg(1, qr[i] - cnt + 1, qr[i], 1);
			}
			else if(op[i] == 1)
			{
				segchg(1, ql[i], ql[i] + cnt - 1, 1);
				segchg(1, ql[i] + cnt, qr[i], 0);
			}
		}
		int pos = segsum(1, q, q);
		if(pos == 1)
		{
			left = mid + 1;
			ans = mid;
		}
		else
		{
			rght = mid - 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
