#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int INF = 1e8;
int n, m;
struct Node
{
	int s[2], fa;
	int v, sz;
	int flag;
};
Node tr[N];
int rt;
void maintain(int p)
{
	tr[p].sz = tr[tr[p].s[0]].sz + tr[tr[p].s[1]].sz + 1;
}
void pushdown(int p)
{
	if(tr[p].flag)
	{
		if(tr[p].s[0])tr[tr[p].s[0]].flag ^= 1;
		if(tr[p].s[1])tr[tr[p].s[1]].flag ^= 1;
		swap(tr[p].s[0], tr[p].s[1]);
		tr[p].flag = 0;
	}
}
void rotate(int x)
{
	int y = tr[x].fa, z = tr[y].fa;
	int k = (tr[y].s[1] == x) ? 1 : 0;
	tr[z].s[tr[z].s[1] == y] = x, tr[x].fa = z;
	tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].fa = y;
	tr[x].s[k ^ 1] = y, tr[y].fa = x;
	maintain(y); maintain(x);
}
void splay(int x, int k)
{
	while(tr[x].fa != k)
	{
		int y = tr[x].fa, z = tr[y].fa;
		pushdown(z), pushdown(y), pushdown(x);
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k)rt = x;
}
void build(int &p, int l, int r)
{
	if(l > r)return;
	int mid = (l + r) >> 1;
	p = mid;
	if(l == r)
	{
		tr[p].sz = 1;
		return;
	}
	if(l < mid)
	{
		build(tr[p].s[0], l, mid - 1);
		tr[tr[p].s[0]].fa = p;
	}
	if(r > mid)
	{
		build(tr[p].s[1], mid + 1, r);
		tr[tr[p].s[1]].fa = p;
	}
	maintain(p);
}
int get_k(int k)
{
	int p = rt;
	while(true)
	{
		pushdown(p);
		if(tr[tr[p].s[0]].sz >= k && tr[p].s[0])p = tr[p].s[0];
		else
		{
			k -= tr[tr[p].s[0]].sz + 1;
			if(k == 0)return p;
			else p = tr[p].s[1];
		}
	}
}
struct TBS
{
	int x, pos;
	bool operator < (const TBS &a)const
	{
		return (x == a.x) ? pos < a.pos : x < a.x;
	}
}p[N];
void init()
{
	for(int i = 1; i <= n + 2; i++)
		tr[i] = { {0,0},0,0,0,0 };
}
void solve()
{
	p[1] = { -INF,1 }, p[n + 2] = { INF,n + 2 };
	for(int i = 2; i <= n + 1; i++)
	{
		scanf("%d", &p[i].x);
		p[i].pos = i;
	}
	sort(p + 2, p + 2 + n);
	build(rt, 1, n + 2);
	for(int i = 2; i <= n; i++)
	{
		splay(p[i].pos, 0);
		int ans = tr[tr[rt].s[0]].sz;
		printf("%d ", ans);
		int L = get_k(i - 1);
		int R = get_k(ans + 2);
		splay(L, 0); splay(R, L);
		tr[tr[R].s[0]].flag ^= 1;
	}
	printf("%d\n", n);
	return;
}
int main()
{
	scanf("%d", &n);
	while(n != 0)
	{
		init();
		solve();
		scanf("%d", &n);
	}
	return 0;
}
