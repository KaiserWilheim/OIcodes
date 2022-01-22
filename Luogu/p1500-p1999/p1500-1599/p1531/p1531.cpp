#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
struct node
{
	int l, r;
	ll max;
}tr[N<<2];
ll a[N];
int n, m;
void pushup(int p)
{
	tr[p].max = max(tr[p << 1].max, tr[p << 1 | 1].max);
	return;
}
void build(int p, int l, int r)
{
	tr[p] = { l,r,-114514 };
	if(l == r)
	{
		tr[p].max = a[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}
void segadd(int p, int ed, ll k)
{
	auto &u = tr[p];
	if((u.l == ed) && (u.r == ed))
	{
		u.max = max(u.max, k);
		return;
	}
	int mid = (u.r + u.l) >> 1;
	if(ed <= mid)segadd(p << 1, ed, k);
	if(ed > mid)segadd(p << 1 | 1, ed, k);
	pushup(p);
	return;
}
ll segmax(int p, int l, int r)
{
	auto &u = tr[p];
	if((u.l >= l) && (u.r <= r))return u.max;
	ll res = -114514;
	int mid = (u.r + u.l) >> 1;
	if(l <= mid)res = max(res, segmax(p << 1, l, r));
	if(r > mid)res = max(res, segmax(p << 1 | 1, l, r));
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	build(1, 1, n);
	while(m--)
	{
		char op;
		int x;
		ll y;
		cin >> op;
		scanf("%d%lld", &x, &y);
		if(op == 'Q')
		{
			printf("%lld\n", segmax(1, x, y));
		}
		else if(op == 'U')
		{
			segadd(1, x, y);
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
