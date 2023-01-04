#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 150010, M = N << 1;
#define lowbit(x) ((x)&-(x))
int n, m;
int a[N], b[N];
int c[N];
void addtr(int x, int v)
{
	for(int i = x; i <= n; i += lowbit(i))
		c[i] += v;
}
int sumtr(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += c[i];
	return res;
}
struct Node
{
	int ls, rs;
	int w;
};
Node tr[N << 6];
int rt[N], idx;
void segchg(int &p, int l, int r, int pos, int k)
{
	if(!p)p = ++idx;
	tr[p].w += k;
	if(l == r)return;
	int mid = (l + r) >> 1;
	if(pos <= mid)segchg(tr[p].ls, l, mid, pos, k);
	else segchg(tr[p].rs, mid + 1, r, pos, k);
}
int segsum(int p, int l, int r, int ql, int qr)
{
	if(!p)return 0;
	if(l >= ql && r <= qr)return tr[p].w;
	int mid = (l + r) >> 1;
	int res = 0;
	if(ql <= mid)res += segsum(tr[p].ls, l, mid, ql, qr);
	if(qr > mid)res += segsum(tr[p].rs, mid + 1, r, ql, qr);
	return res;
}
ll ans;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[a[i]] = i;
		ans += sumtr(n) - sumtr(a[i]);
		addtr(a[i], 1);
	}
	for(int i = 1; i <= n; i++)
		for(int x = i; x <= n; x += lowbit(x))
			segchg(rt[x], 1, n, a[i], 1);
	while(m--)
	{
		printf("%lld\n", ans);
		int x;
		scanf("%d", &x);
		int p = b[x];
		for(int i = p - 1; i; i -= lowbit(i))
			ans -= segsum(rt[i], 1, n, a[p] + 1, n);
		for(int i = n; i; i -= lowbit(i))
			ans -= segsum(rt[i], 1, n, 1, a[p] - 1);
		for(int i = p; i; i -= lowbit(i))
			ans += segsum(rt[i], 1, n, 1, a[p] - 1);
		for(int i = p; i <= n; i += lowbit(i))
			segchg(rt[i], 1, n, a[p], -1);
	}
	return 0;
}
