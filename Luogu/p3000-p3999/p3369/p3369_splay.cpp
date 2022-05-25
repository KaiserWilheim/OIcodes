#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
struct Node
{
	int s[2], fa;
	int v, w;
	int sz;
	void init(int _v, int _fa)
	{
		v = _v, fa = _fa;
		sz = w = 1;
	}
	void clear()
	{
		s[0] = s[1] = 0;
		fa = 0;
		v = w = 0;
		sz = 0;
	}
}tr[N];
int rt, idx;
void pushup(int p)
{
	tr[p].sz = tr[p].w;
	if(tr[p].s[0])tr[p].sz += tr[tr[p].s[0]].sz;
	if(tr[p].s[1])tr[p].sz += tr[tr[p].s[1]].sz;
}
void rotate(int x)
{
	int y = tr[x].fa, z = tr[y].fa;
	int k = tr[y].s[1] == x;
	tr[z].s[tr[z].s[1] == y] = x, tr[x].fa = z;
	tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].fa = y;
	tr[x].s[k ^ 1] = y, tr[y].fa = x;
	pushup(y), pushup(x);
}
void splay(int x, int k)
{
	while(tr[x].fa != k)
	{
		int y = tr[x].fa, z = tr[y].fa;
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y))
				rotate(x);
			else
				rotate(y);
		}
		rotate(x);
	}
	if(!k) rt = x;
}
void insert(int k)
{
	if(!rt)
	{
		tr[++idx].init(k, 0);
		rt = idx;
		return;
	}
	int p = rt, fa = 0;
	while(true)
	{
		if(tr[p].v == k)
		{
			tr[p].w++;
			pushup(p), pushup(fa);
			splay(p, 0);
			break;
		}
		fa = p;
		p = tr[p].s[tr[p].v < k];
		if(!p)
		{
			tr[++idx].init(k, fa);
			tr[fa].s[tr[fa].v < k] = idx;
			pushup(fa);
			splay(idx, 0);
			break;
		}
	}
}
int get_rk(int k)
{
	int res = 0, p = rt;
	while(true)
	{
		if(k < tr[p].v)
		{
			p = tr[p].s[0];
		}
		else
		{
			if(tr[p].s[0])res += tr[tr[p].s[0]].sz;
			if(k == tr[p].v)
			{
				splay(p, 0);
				return res + 1;
			}
			res += tr[p].w;
			p = tr[p].s[1];
		}
	}
}
int get_k(int k)
{
	int p = rt;
	while(true)
	{
		if(tr[tr[p].s[0]].sz >= k && tr[p].s[0])
		{
			p = tr[p].s[0];
		}
		else
		{
			k -= tr[p].w;
			if(tr[p].s[0])k -= tr[tr[p].s[0]].sz;
			if(k <= 0)
			{
				splay(p, 0);
				return tr[p].v;
			}
			p = tr[p].s[1];
		}
	}
}
int precsr()
{
	int p = tr[rt].s[0];
	if(!p)return p;
	while(tr[p].s[1])p = tr[p].s[1];
	splay(p, 0);
	return p;
}
int succsr()
{
	int p = tr[rt].s[1];
	if(!p)return p;
	while(tr[p].s[0])p = tr[p].s[0];
	splay(p, 0);
	return p;
}
void loschn(int k)
{
	get_rk(k);
	if(tr[rt].w > 1)
	{
		tr[rt].w--;
		pushup(rt);
		return;
	}
	if(!tr[rt].s[0] && !tr[rt].s[1])
	{
		tr[rt].clear();
		rt = 0;
		return;
	}
	if(!tr[rt].s[0])
	{
		int p = rt;
		rt = tr[rt].s[1];
		tr[rt].fa = 0;
		tr[p].clear();
		return;
	}
	if(!tr[rt].s[1])
	{
		int p = rt;
		rt = tr[rt].s[0];
		tr[rt].fa = 0;
		tr[p].clear();
		return;
	}
	int p = rt;
	int x = precsr();
	tr[tr[p].s[1]].fa = x;
	tr[x].s[1] = tr[p].s[1];
	tr[p].clear();
	pushup(rt);
}
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int op, x;
		scanf("%d%d", &op, &x);
		if(op == 1)
			insert(x);
		else if(op == 2)
			loschn(x);
		else if(op == 3)
			printf("%d\n", get_rk(x));
		else if(op == 4)
			printf("%d\n", get_k(x));
		else if(op == 5)
			insert(x), printf("%d\n", tr[precsr()].v), loschn(x);
		else if(op == 6)
			insert(x), printf("%d\n", tr[succsr()].v), loschn(x);
	}
	return 0;
}
