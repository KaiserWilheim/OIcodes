#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, m, k;
int ms;
int a[N], sum[N];
int bl[N];
struct Node
{
	int l, r, id, op;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		if(bl[lhs.l] != bl[rhs.l])return lhs.l < rhs.l;
		if(bl[lhs.l] & 1)return lhs.r < rhs.r;
		else return lhs.r > rhs.r;
	}
};
Node q[M];
ll cntl[N], cntr[N];
ll ans, res[N];
void addl(int x)
{
	++cntl[a[x]];
	ans += cntr[a[x]];
}
void dell(int x)
{
	--cntl[a[x]];
	ans -= cntr[a[x]];
}
void addr(int x)
{
	++cntr[a[x]];
	ans += cntl[a[x]];
}
void delr(int x)
{
	--cntr[a[x]];
	ans -= cntl[a[x]];
}
int main()
{
	scanf("%d", &n);
	int S = sqrt(n) + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		bl[i] = ((i - 1) / S) + 1;
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int l1, l2, r1, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		q[++ms] = { r1,r2,i,1 };
		q[++ms] = { r1,l2 - 1,i,-1 };
		q[++ms] = { l1 - 1,r2,i,-1 };
		q[++ms] = { l1 - 1,l2 - 1,i,1 };
	}
	for(int i = 1; i <= ms; i++)
		if(q[i].l > q[i].r)swap(q[i].l, q[i].r);
	sort(q + 1, q + 1 + ms);
	int l = 0, r = 0;
	for(int i = 1; i <= ms; i++)
	{
		while(l > q[i].l)dell(l--);
		while(l < q[i].l)addl(++l);
		while(r > q[i].r)delr(r--);
		while(r < q[i].r)addr(++r);
		res[q[i].id] += ans * q[i].op;
	}
	for(int i = 1; i <= m; i++)
		printf("%lld\n", res[i]);
	return 0;
}
