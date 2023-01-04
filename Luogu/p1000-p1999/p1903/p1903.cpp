#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(i) ((i)&-(i))
const int N = 500010, M = N << 1;
int n, m;
namespace Tree
{
	const double alpha = 0.75;
	struct Node
	{
		int ls, rs;
		int w, wn;
		int s, sz, sd;
	};
	Node tr[N];
	int rt[M], idx;
	int rec[N], tt;

	int newnode()
	{
		int res;
		if(tt)res = rec[tt--];
		else res = ++idx;
		tr[res] = { 0,0,0,0,0,0,0 };
		return res;
	}
	void calc(int p)
	{
		tr[p].s = tr[tr[p].ls].s + tr[tr[p].rs].s + 1;
		tr[p].sz = tr[tr[p].ls].sz + tr[tr[p].rs].sz + tr[p].wn;
		tr[p].sd = tr[tr[p].ls].sd + tr[tr[p].rs].sd + (tr[p].wn != 0);
	}
	bool canrbu(int p)
	{
		if(!tr[p].wn)return false;
		if(alpha * tr[p].s <= double(max(tr[tr[p].ls].s, tr[tr[p].rs].s)))return true;
		if(double(tr[p].sd) <= alpha * tr[p].s)return true;
		return false;
	}
	pair<int, int> ldr[N];
	int ldc;
	void rbuunf(int p)
	{
		if(!p)return;
		rbuunf(tr[p].ls);
		if(tr[p].wn)ldr[++ldc] = make_pair(tr[p].w, tr[p].wn);
		rec[++tt] = p;
		rbuunf(tr[p].rs);
	}
	int rbubld(int l, int r)
	{
		if(l > r)return 0;
		int mid = (l + r) >> 1;
		int p = newnode();
		tr[p].w = ldr[mid].first, tr[p].wn = ldr[mid].second;
		tr[p].ls = rbubld(l, mid - 1);
		tr[p].rs = rbubld(mid + 1, r);
		calc(p);
		return p;
	}
	void rbuild(int &p)
	{
		ldc = 0;
		rbuunf(p);
		p = rbubld(0, ldc);
	}
	int rank(int p, int k)
	{
		int res = 1;
		while(p)
		{
			if(tr[p].w >= k)p = tr[p].ls;
			else
			{
				res += tr[tr[p].ls].sz + tr[p].wn;
				p = tr[p].rs;
			}
		}
		return res;
	}
	void insert(int &p, int k)
	{
		if(!p)
		{
			p = newnode();
			tr[p].w = k;
			tr[p].wn = tr[p].s = tr[p].sz = tr[p].sd = 1;
			return;
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
		if(tr[p].wn && tr[tr[p].ls].sz < k && k <= tr[tr[p].ls].sz + tr[p].wn)
			tr[p].wn--;
		else if(tr[tr[p].ls].sz + tr[p].wn < k)
			loschn(tr[p].rs, k - tr[tr[p].ls].sz - tr[p].wn);
		else loschn(tr[p].ls, k);
		calc(p);
		if(canrbu(p))rbuild(p);
	}
	void segins(int x, int k)
	{
		if(!x)return;
		for(int i = x; i <= n; i += lowbit(i))
			insert(rt[i], k);
	}
	void segdel(int x, int k)
	{
		if(!x)return;
		for(int i = x; i <= n; i += lowbit(i))
			loschn(rt[i], rank(rt[i], k));
	}
	int query(int l, int r, int k)
	{
		int res = 0;
		for(int i = r; i; i -= lowbit(i))
			res += rank(rt[i], k + 1) - 1;
		for(int i = l - 1; i; i -= lowbit(i))
			res -= rank(rt[i], k + 1) - 1;
		return res;
	}
}
namespace Set
{
	set<int>s[M];
	void insert(int x, int k) { s[x].insert(k); }
	void loschn(int x, int k) { s[x].erase(s[x].find(k)); }
	pair<int, int>find(int x, int k)
	{
		auto it = s[x].find(k);
		pair<int, int>res = make_pair(0, 0);
		if(it != s[x].begin())it--, res.first = *it, it++;
		it++;
		if(it != s[x].end())res.second = *it;
		return res;
	}
}
int num[N], lst[M];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &num[i]);
		Tree::segins(i, lst[num[i]]);
		Set::insert(num[i], i);
		lst[num[i]] = i;
	}
	char op[10];
	for(int i = 1; i <= m; i++)
	{
		scanf("%s", op);
		int x, y;
		scanf("%d%d", &x, &y);
		if(op[0] == 'Q')
		{
			printf("%d\n", Tree::query(x, y, x - 1));
		}
		else
		{
			auto s = Set::find(num[x], x);
			Tree::segdel(x, s.first);
			Tree::segdel(s.second, x);
			Tree::segins(s.second, s.first);
			Set::loschn(num[x], x);
			num[x] = y;
			Set::insert(num[x], x);
			s = Set::find(num[x], x);
			Tree::segdel(s.second, s.first);
			Tree::segins(s.second, x);
			Tree::segins(x, s.first);
		}
	}
	return 0;
}
