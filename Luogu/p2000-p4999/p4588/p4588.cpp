#include <bits/stdc++.h>
using namespace std;
int n, mod;
const int N = 100010;
//int a[N];
struct segtree
{
	int l, r;
	long long v;
}node[N << 2];
void build(int p, int l, int r)
{
	node[p].l = l;
	node[p].r = r;
	if(l == r)
	{
		node[p].v = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	node[p].v = (node[p << 1].v * node[p << 1 | 1].v)%mod;
	return;
}
void segpd(int p, int ed, int k)
{
	if((node[p].r == ed) && (node[p].l == ed))
	{
		node[p].v = k;
		return;
	}
	int mid = (node[p].r + node[p].l) >> 1;
	if(mid >= ed)segpd(p << 1, ed, k);
	if(mid < ed)segpd(p << 1 | 1, ed, k);
	node[p].v = (node[p << 1].v * node[p << 1 | 1].v)%mod;
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int m;
		scanf("%d%d", &m,&mod);
		build(1, 1, N);
		int cnt = 1;
		for(int i = 1; i <= m; i++)
		{
			int op, x;
			scanf("%d%d", &op, &x);
			if(op == 1)
			{
				segpd(1, i + 1, x);
				printf("%lld\n", node[1].v%mod);
			}
			else if(op == 2)
			{
				segpd(1, x + 1, 1);
				printf("%lld\n", node[1].v%mod);
			}
			else
			{
				puts("Youwike AK IOI!");
			}
		}
	}
	return 0;
}
