#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int inline read()
{
	int x = 0, f = 1; char c = getchar();
	while(c > '9' || c < '0') { if(c == '-')f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n, m;
struct Node
{
	int s[2], fa;
	int v, sz;
};
Node tr[N];
int idx, rt;
int pos[N];
void maintain(int p)
{
	tr[p].sz = tr[tr[p].s[0]].sz + tr[tr[p].s[1]].sz + 1;
	pos[tr[tr[p].s[0]].v] = tr[p].s[0];
	pos[tr[tr[p].s[1]].v] = tr[p].s[1];
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
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k)rt = x;
	pos[tr[x].v] = x;
}
void insert(int x)
{
	idx++;
	tr[idx].v = x, tr[idx].sz = 1;
	pos[x] = idx;
	if(idx > 1)
	{
		tr[idx - 1].s[1] = idx;
		tr[idx].fa = idx - 1;
		splay(idx, 0);
	}
}
int find(int p, int k)
{
	int u = tr[p].s[0];
	if(tr[u].sz + 1 == k) return p;
	else if(tr[u].sz >= k) return find(u, k);
	else return find(tr[p].s[1], k - tr[u].sz - 1);
}
void top(int p)
{
	splay(p, 0);
	if(!tr[p].s[0]) return;
	if(!tr[p].s[1])
	{
		tr[p].s[1] = tr[p].s[0];
		tr[p].s[0] = 0;
	}
	else
	{
		int u = find(rt, tr[tr[p].s[0]].sz + 2);
		tr[tr[rt].s[0]].fa = u;
		tr[u].s[0] = tr[rt].s[0];
		tr[rt].s[0] = 0;
		splay(u, 0);
	}
}
void bottom(int p)
{
	splay(p, 0);
	if(!tr[p].s[1]) return;
	if(!tr[p].s[0])
	{
		tr[p].s[0] = tr[p].s[1];
		tr[p].s[1] = 0;
	}
	else
	{
		int u = find(rt, tr[tr[p].s[0]].sz);
		tr[tr[rt].s[1]].fa = u;
		tr[u].s[1] = tr[rt].s[1];
		tr[rt].s[1] = 0;
		splay(u, 0);
	}
}
void ins(int f, int p)
{
	if(!f) return;
	splay(pos[p], 0);
	int u = find(rt, tr[tr[pos[p]].s[0]].sz + (f == 1 ? 2 : 0));
	int x1 = tr[u].v, x2 = pos[p];
	swap(pos[p], pos[x1]);
	swap(tr[x2].v, tr[u].v);
}
void getans(int x)
{
	splay(x, 0);
	printf("%d\n", tr[tr[x].s[0]].sz);
}
int main()
{
	cin >> n >> m;
	rt = 1;
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		insert(x);
	}
	while(m--)
	{
		string op;
		cin >> op;
		if(op[0] == 'T')top(pos[read()]);
		else if(op[0] == 'B')bottom(pos[read()]);
		else if(op[0] == 'I')ins(read(), read());
		else if(op[0] == 'A')getans(pos[read()]);
		else if(op[0] == 'Q')printf("%d\n", tr[find(rt, read())].v);
	}
	return 0;
}
