#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
struct Trie
{
	int s[2];
	int sz;
};
Trie tr[N * 30];
int rt[N], idx, now;
void insert(int x)
{
	int p = ++idx, q = rt[now];
	rt[++now] = p;
	tr[p] = tr[q];
	tr[p].sz++;
	for(int i = 20; ~i; i--)
	{
		int c = (x >> i) & 1;
		tr[p].s[c] = ++idx;
		p = tr[p].s[c], q = tr[q].s[c];
		tr[p] = tr[q];
		tr[p].sz++;
	}
}
int query1(int l, int r, int x)
{
	int p = rt[r], q = rt[l - 1];
	int res = 0;
	for(int i = 20; ~i; i--)
	{
		int c = (x >> i) & 1;
		if(tr[tr[p].s[c ^ 1]].sz > tr[tr[q].s[c ^ 1]].sz)
		{
			p = tr[p].s[c ^ 1], q = tr[q].s[c ^ 1];
			res |= ((c ^ 1) << i);
		}
		else
		{
			p = tr[p].s[c], q = tr[q].s[c];
			res |= (c << i);
		}
	}
	return res;
}
int query3(int l, int r, int x)
{
	int p = rt[r], q = rt[l - 1];
	int res = 0;
	for(int i = 20; ~i; i--)
	{
		int c = (x >> i) & 1;
		if(c)
		{
			res += tr[tr[p].s[0]].sz - tr[tr[q].s[0]].sz;
			p = tr[p].s[1], q = tr[q].s[1];
		}
		else
		{
			p = tr[p].s[0], q = tr[q].s[0];
		}
	}
	return res + tr[p].sz - tr[q].sz;
}
int query4(int l, int r, int x)
{
	int p = rt[r], q = rt[l - 1];
	int res = 0;
	for(int i = 20; ~i; i--)
	{
		if(tr[tr[p].s[0]].sz - tr[tr[q].s[0]].sz >= x)
		{
			p = tr[p].s[0], q = tr[q].s[0];
		}
		else
		{
			res |= (1 << i);
			x -= tr[tr[p].s[0]].sz - tr[tr[q].s[0]].sz;
			p = tr[p].s[1], q = tr[q].s[1];
		}
	}
	return res;
}
int main()
{
	scanf("%d", &m);
	while(m--)
	{
		int op, x, l, r;
		scanf("%d", &op);
		if(op == 0)
		{
			scanf("%d", &x);
			insert(x);
		}
		else if(op == 1)
		{
			scanf("%d%d%d", &l, &r, &x);
			int res = query1(l, r, x);
			printf("%d\n", res);
		}
		else if(op == 2)
		{
			scanf("%d", &x);
			now -= x;
		}
		else if(op == 3)
		{
			scanf("%d%d%d", &l, &r, &x);
			int res = query3(l, r, x);
			printf("%d\n", res);
		}
		else
		{
			scanf("%d%d%d", &l, &r, &x);
			int res = query4(l, r, x);
			printf("%d\n", res);
		}
	}
	return 0;
}