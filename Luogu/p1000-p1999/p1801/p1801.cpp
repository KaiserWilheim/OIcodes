#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
double alpha = 0.75;
struct Scapegoat
{
	int ls, rs;
	int w, wn;
	int s, sz, sd;
}tr[N];
int cnt, rt;
void calc(int p)
{
	tr[p].s = tr[tr[p].ls].s + tr[tr[p].rs].s + 1;
	tr[p].sz = tr[tr[p].ls].sz + tr[tr[p].rs].sz + tr[p].wn;
	tr[p].sd = tr[tr[p].ls].sd + tr[tr[p].rs].sd + (tr[p].wn != 0);
}
bool canrbu(int p)
{
	return tr[p].wn && (alpha * tr[p].s <= ( double )max(tr[tr[p].ls].s, tr[tr[p].rs].s) || ( double )tr[p].sd <= alpha * tr[p].s);
}
int ldr[N];
void rbuunf(int &ldc, int p)
{
	if(!p)return;
	rbuunf(ldc, tr[p].ls);
	if(tr[p].wn)ldr[ldc++] = p;
	rbuunf(ldc, tr[p].rs);
}
int rbubld(int l, int r)
{
	if(l >= r)return 0;
	int mid = (l + r) >> 1;
	tr[ldr[mid]].ls = rbubld(l, mid);
	tr[ldr[mid]].rs = rbubld(mid + 1, r);
	calc(ldr[mid]);
	return ldr[mid];
}
void rbuild(int &p)
{
	int ldc = 0;
	rbuunf(ldc, p);
	p = rbubld(0, ldc);
}
void insert(int &p, int k)
{
	if(!p)
	{
		p = ++cnt;
		if(!rt)rt = 1;
		tr[p].w = k;
		tr[p].ls = tr[p].rs = 0;
		tr[p].wn = tr[p].s = tr[p].sz = tr[p].sd = 1;
	}
	else
	{
		if(tr[p].w == k)tr[p].wn++;
		else if(tr[p].w < k)insert(tr[p].rs, k);
		else insert(tr[p].ls, k);
		calc(p);
		if(canrbu(p))rbuild(p);
	}
}
void loschn(int &p, int k)
{
	if(!p)return;
	if(tr[p].w == k)
	{
		if(tr[p].wn)tr[p].wn--;
	}
	else
	{
		if(tr[p].w < k)loschn(tr[p].rs, k);
		else loschn(tr[p].ls, k);
	}
	calc(p);
	if(canrbu(p))rbuild(p);
}
int getk(int p, int k)
{
	if(!p)
		return 0;
	else if(tr[tr[p].ls].sz < k && k <= tr[tr[p].ls].sz + tr[p].wn)
		return tr[p].w;
	else if(tr[tr[p].ls].sz + tr[p].wn < k)
		return getk(tr[p].rs, k - tr[tr[p].ls].sz - tr[p].wn);
	else
		return getk(tr[p].ls, k);
}
int idx = 0;
int a[N], u[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &u[i]);
	int now = 1;
	for(int i = 1; i <= n; i++)
	{
		insert(rt, a[i]);
		while(u[now] == i)
		{
			idx++;
			printf("%d\n", getk(rt, idx));
			now++;
		}
	}
	return 0;
}
