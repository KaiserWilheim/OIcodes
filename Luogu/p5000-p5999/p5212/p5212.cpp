#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1200050, M = 3000050;

char s[M];
string chars;

int mask;
void decodeWithMask(int mask)
{
	scanf("%s", s);
	chars = s;
	for(int j = 0; j < chars.length(); j++)
	{
		mask = (mask * 131 + j) % chars.length();
		char t = chars[j];
		chars[j] = chars[mask];
		chars[mask] = t;
	}
}

struct link_cut_tree
{
	int w[N], tag[N], son[N][2], fa[N], st[N];

	void add(int x, int y)
	{
		if(x)
		{
			w[x] += y;
			tag[x] += y;
		}
	}

	void push_down(int x)
	{
		int ls = son[x][0], rs = son[x][1];
		if(tag[x])
		{
			add(ls, tag[x]);
			add(rs, tag[x]);
			tag[x] = 0;
		}
	}

	bool isroot(int x)
	{
		return son[fa[x]][0] != x && son[fa[x]][1] != x;
	}

	void rotate(int x)
	{
		int y = fa[x], z = fa[y];
		int l, r;
		l = (son[y][0] == x) ? 0 : 1;
		r = l ^ 1;
		if(!isroot(y))son[z][(son[z][0] == y ? 0 : 1)] = x;
		fa[x] = z;
		fa[y] = x;
		fa[son[x][r]] = y;
		son[y][l] = son[x][r];
		son[x][r] = y;
	}

	void splay(int x)
	{
		int cnt = 0;
		st[++cnt] = x;
		for(int i = x; !isroot(i); i = fa[i])st[++cnt] = fa[i];
		while(cnt)push_down(st[cnt--]);
		while(!isroot(x))
		{
			int y = fa[x], z = fa[y];
			if(!isroot(y))rotate((son[y][0] == x) ^ (son[z][0] == y) ? x : y);
			rotate(x);
		}
	}

	void access(int x)
	{
		for(int y = 0; x; x = fa[x])
		{
			splay(x);
			son[x][1] = y;
			y = x;
		}
	}

	void link(int x, int y)
	{
		fa[x] = y;
		access(y);
		splay(y);
		add(y, w[x]);
	}

	void cut(int x)
	{
		access(x);
		splay(x);
		add(son[x][0], -w[x]);
		fa[son[x][0]] = 0;
		son[x][0] = 0;
	}

}tr;

struct suffixautomaton
{
	int cnt, last;

	int fa[N], len[N], trans[N][26];

	void insert(int c)
	{
		int p = last, np = ++cnt;
		last = np;
		len[np] = len[p] + 1;
		tr.w[np] = 1;
		for(; p && !trans[p][c]; p = fa[p])trans[p][c] = np;
		if(!p)
		{
			fa[np] = 1;
			tr.link(np, 1);
		}
		else
		{
			int q = trans[p][c];
			if(len[p] + 1 == len[q])
			{
				fa[np] = q;
				tr.link(np, q);
			}
			else
			{
				int nq = ++cnt;
				len[nq] = len[p] + 1;
				memcpy(trans[nq], trans[q], sizeof(trans[q]));
				fa[nq] = fa[q];
				tr.link(nq, fa[q]);
				fa[q] = fa[np] = nq;
				tr.cut(q);
				tr.link(q, nq);
				tr.link(np, nq);
				for(; trans[p][c] == q; p = fa[p])
					trans[p][c] = nq;
			}
		}
	}

	void build()
	{
		cnt = last = 1;
		scanf("%s", s);
		int len = strlen(s);
		for(int i = 0; i < len; i++)insert(s[i] - 'A');
	}

	void add()
	{
		decodeWithMask(mask);
		int len = chars.length();
		for(int i = 0; i < len; i++)insert(chars[i] - 'A');
	}

	int query()
	{
		decodeWithMask(mask);
		int p = 1, len = chars.length();
		for(int i = 0; i < len; i++)
			if(!(p = trans[p][chars[i] - 'A']))
				return 0;
		tr.splay(p);
		return tr.w[p];
	}

}sam;

int main()
{
	int T;
	scanf("%d", &T);
	sam.build();
	while(T--)
	{
		char str[10];
		scanf("%s", str);
		if(str[0] == 'A')
		{
			sam.add();
		}
		else
		{
			int ans = sam.query();
			printf("%d\n", ans);
			mask ^= ans;
		}
	}
	return 0;
}
