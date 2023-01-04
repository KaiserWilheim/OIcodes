#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
ll n, m;
double alpha = 0.75;
struct Scapegoat
{
	int ls, rs;
	ll w, wn;
	int s, sz, sd;
	ll sum;
}tr[N];
int cnt, rt;
void calc(int p)
{
	tr[p].s = tr[tr[p].ls].s + tr[tr[p].rs].s + 1;
	tr[p].sz = tr[tr[p].ls].sz + tr[tr[p].rs].sz + tr[p].wn;
	tr[p].sd = tr[tr[p].ls].sd + tr[tr[p].rs].sd + (tr[p].wn != 0);
	tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum + tr[p].wn * tr[p].w;
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
void insert(int &p, ll k)
{
	if(!p)
	{
		p = ++cnt;
		if(!rt)rt = 1;
		tr[p].w = k;
		tr[p].ls = tr[p].rs = 0;
		tr[p].wn = tr[p].s = tr[p].sz = tr[p].sd = 1;
		tr[p].sum = k;
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
void loschn(int &p, ll k)
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
ll uprgtr(int p, ll k)
{
	if(!p)
		return 0;
	else if(tr[p].w == k && tr[p].wn)
		return tr[tr[p].ls].sz;
	else if(tr[p].w < k)
		return tr[tr[p].ls].sz + tr[p].wn + uprgtr(tr[p].rs, k);
	else
		return uprgtr(tr[p].ls, k);
}
ll uprsum(int p, ll k)
{
	if(!p)
		return 0;
	else if(tr[p].w == k && tr[p].wn)
		return tr[tr[p].ls].sum;
	else if(tr[p].w < k)
		return tr[tr[p].ls].sum + tr[p].wn * tr[p].w + uprsum(tr[p].rs, k);
	else
		return uprsum(tr[p].ls, k);
}
ll suml, sumt;
ll l[N], t[N];
int main()
{
	scanf("%lld%lld", &n, &m);
	int temp[N];
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &l[i], &t[i]);
		suml += l[i];
		insert(rt, t[i]);
		temp[i] = t[i];
	}
	sort(temp + 1, temp + 1 + n);
	for(int i = 1; i <= n; i++)
		sumt += (n - i + 1) * temp[i];
	printf("%lld\n", suml - sumt);
	while(m--)
	{
		int a;
		ll b, c;
		scanf("%d%lld%lld", &a, &b, &c);
		suml -= l[a] - b;
		l[a] = b;
		ll sum1 = uprsum(rt, t[a]), cnt1 = uprgtr(rt, t[a]);
		loschn(rt, t[a]);
		insert(rt, c);
		ll sum2 = uprsum(rt, c), cnt2 = uprgtr(rt, c);
		sumt += c * (n - cnt2) + sum2 - t[a] * (n - cnt1) - sum1;
		t[a] = c;
		printf("%lld\n", suml - sumt);
	}
}
