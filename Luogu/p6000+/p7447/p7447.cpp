#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 500010, M = 200010;
const int B = 32, K = 40;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int a[N];
int bl[N], pos[N];
int minn, maxn; ll sum;
struct Stat
{
	int l, r;
	bool flag;
};
Stat TR[M];
void build(int p, int l, int r)
{
	TR[p].l = l, TR[p].r = r;
	if(r - l <= K)
	{
		TR[p].flag = true;
		for(int i = l; i <= r; i++)
			pos[i] = p;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
queue<int>down;
struct SegTree
{
	int id;
	int L, R;
	struct Node
	{
		int maxn, minn;
		int cnt;
		ll sum;
		ll tag;
		Node() { maxn = cnt = sum = tag = 0, minn = 2e9; }
	};
	Node tr[M];
	void update(int p)
	{
		tr[p].sum = tr[p].cnt = tr[p].maxn = 0, tr[p].minn = 2e9;
		for(int i = TR[p].l; i <= TR[p].r; i++)
		{
			if(bl[i] != id)continue;
			tr[p].cnt++;
			tr[p].sum += a[i];
			tr[p].maxn = max(tr[p].maxn, a[i]);
			tr[p].minn = min(tr[p].minn, a[i]);
		}
	}
	void pushup(int p)
	{
		if(TR[p].flag)update(p);
		else
		{
			tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
			tr[p].cnt = tr[p << 1].cnt + tr[p << 1 | 1].cnt;
			tr[p].maxn = max(tr[p << 1].maxn, tr[p << 1 | 1].maxn);
			tr[p].minn = min(tr[p << 1].minn, tr[p << 1 | 1].minn);
		}
	}
	void pushtag(int p, int q)
	{
		tr[q].tag += tr[p].tag;
		tr[q].minn += tr[p].tag;
		tr[q].maxn += tr[p].tag;
		tr[q].sum += tr[q].cnt * tr[p].tag;
	}
	void pushdown(int p)
	{
		if(!tr[p].tag)return;
		if(TR[p].flag)
		{
			for(int i = TR[p].l; i <= TR[p].r; i++)
			{
				if(bl[i] != id)continue;
				a[i] += tr[p].tag;
			}
		}
		else
		{
			pushtag(p, p << 1);
			pushtag(p, p << 1 | 1);
		}
		tr[p].tag = 0;
	}
	void pushup_path(int p)
	{
		pushup(p);
		if(p > 1)pushup_path(p >> 1);
	}
	void pushdown_path(int p)
	{
		if(p > 1)pushdown_path(p >> 1);
		pushdown(p);
	}
	void add(int p)
	{
		int tmp = a[p];
		pushdown_path(pos[p]);
		a[p] = tmp;
		p = pos[p];
		pushup(p);
		pushup_path(p >> 1);
	}
	void segadd(int p, int l, int r, ll k)
	{
		if(tr[p].maxn <= k)return;
		if(l <= TR[p].l && TR[p].r <= r)
		{
			if(tr[p].minn > k)
			{
				tr[p].tag -= k;
				tr[p].minn -= k;
				tr[p].maxn -= k;
				tr[p].sum -= tr[p].cnt * k;
				return;
			}
			pushdown(p);
			if(TR[p].flag)
			{
				for(int i = TR[p].l; i <= TR[p].r; i++)
				{
					if(bl[i] != id)continue;
					a[i] -= (a[i] > k) * k;
				}
				pushup(p);
				return;
			}
			segadd(p << 1, l, r, k);
			segadd(p << 1 | 1, l, r, k);
			pushup(p);
			return;
		}
		pushdown(p);
		if(TR[p].flag)
		{
			for(int i = TR[p].l; i <= TR[p].r; i++)
			{
				if(i >= l && i <= r && bl[i] == id)
					a[i] -= (a[i] > k) * k;
			}
			pushup(p);
			return;
		}
		int mid = (TR[p].l + TR[p].r) >> 1;
		if(l <= mid)segadd(p << 1, l, r, k);
		if(r > mid)segadd(p << 1 | 1, l, r, k);
		pushup(p);
	}
	void segsum(int p, int l, int r)
	{
		if(l <= TR[p].l && TR[p].r <= r)
		{
			minn = min(minn, tr[p].minn);
			maxn = max(maxn, tr[p].maxn);
			sum += tr[p].sum;
			return;
		}
		pushdown(p);
		if(TR[p].flag)
		{
			for(int i = TR[p].l; i <= TR[p].r; i++)
			{
				if(i >= l && i <= r && bl[i] == id)
				{
					minn = min(minn, a[i]);
					maxn = max(maxn, a[i]);
					sum += a[i];
				}
			}
			return;
		}
		int mid = (TR[p].l + TR[p].r) >> 1;
		if(l <= mid)segsum(p << 1, l, r);
		if(r > mid)segsum(p << 1 | 1, l, r);
	}
	void loschn(int p)
	{
		if(tr[p].minn >= L)return;
		pushdown(p);
		if(TR[p].flag)
		{
			tr[p].sum = tr[p].cnt = tr[p].maxn = 0, tr[p].minn = 2e9;
			for(int i = TR[p].l; i <= TR[p].r; i++)
			{
				if(bl[i] != id)continue;
				if(a[i] >= L)
				{
					tr[p].cnt++;
					tr[p].sum += a[i];
					tr[p].maxn = max(tr[p].maxn, a[i]);
					tr[p].minn = min(tr[p].minn, a[i]);
				}
				else
				{
					down.push(i);
					bl[i] = 0;
				}
			}
			return;
		}
		loschn(p << 1);
		loschn(p << 1 | 1);
		pushup(p);
	}
};
SegTree tr[7];
int cnt;
void add(int p)
{
	for(int i = 1; i <= cnt; i++)
	{
		if(tr[i].L <= a[p] && tr[i].R >= a[p])
		{
			bl[p] = i;
			tr[i].add(p);
			return;
		}
	}
}
void segadd(int l, int r, int k)
{
	for(int i = 1; i <= cnt; i++)
	{
		tr[i].segadd(1, l, r, k);
		tr[i].loschn(1);
	}
	while(!down.empty())
	{
		add(down.front());
		down.pop();
	}
}
void segsum(int l, int r)
{
	sum = maxn = 0, minn = 2e9;
	for(int i = 1; i <= cnt; i++)
		tr[i].segsum(1, l, r);
}
int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	build(1, 1, n);
	for(ll j = 1;; j *= B)
	{
		tr[++cnt].L = j;
		tr[cnt].id = cnt;
		tr[cnt].R = j * B - 1;
		if(tr[cnt].R >= 1e9)break;
	}
	for(int i = 1; i <= n; i++)
		add(i);
	int lans = 0;
	while(m--)
	{
		int op, l, r;
		op = read(), l = read() ^ lans, r = read() ^ lans;
		if(op == 1)
		{
			segadd(l, r, read() ^ lans);
		}
		else
		{
			segsum(l, r);
			printf("%lld %d %d\n", sum, minn, maxn);
			lans = sum & ((1 << 20) - 1);
		}
	}
	return 0;
}
