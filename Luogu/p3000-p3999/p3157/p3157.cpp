#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 30000010;
#define lowbit(x) ((x)&-(x))
int n, m;
struct Node
{
	int ls, rs;
	int sum;
};
Node tr[M];
int rt[N], idx;
void insert(int &p, int l, int r, int pos, int k)
{
	if(!p)p = ++idx;
	tr[p].sum += k;
	if(l == r)return;
	int mid = (l + r) >> 1;
	if(pos <= mid)insert(tr[p].ls, l, mid, pos, k);
	else insert(tr[p].rs, mid + 1, r, pos, k);
}
int qa[N], qb[N];
int query(int l, int r, int pos, int flag)
{
	int tta = 0, ttb = 0, sum = 0;
	for(int i = l - 1; i; i -= lowbit(i))qa[++tta] = rt[i];
	for(int i = r; i; i -= lowbit(i))qb[++ttb] = rt[i];
	l = 1, r = n;
	while(l != r)
	{
		int mid = (l + r) >> 1;
		if(pos > mid)
		{
			if(flag)
			{
				for(int i = 1; i <= tta; i++)sum -= tr[tr[qa[i]].ls].sum;
				for(int i = 1; i <= ttb; i++)sum += tr[tr[qb[i]].ls].sum;
			}
			for(int i = 1; i <= tta; i++)qa[i] = tr[qa[i]].rs;
			for(int i = 1; i <= ttb; i++)qb[i] = tr[qb[i]].rs;
			l = mid + 1;
		}
		else
		{
			if(!flag)
			{
				for(int i = 1; i <= tta; i++)sum -= tr[tr[qa[i]].rs].sum;
				for(int i = 1; i <= ttb; i++)sum += tr[tr[qb[i]].rs].sum;
			}
			for(int i = 1; i <= tta; i++)qa[i] = tr[qa[i]].ls;
			for(int i = 1; i <= ttb; i++)qb[i] = tr[qb[i]].ls;
			r = mid;
		}
	}
	return sum;
}
int a[N], pos[N];
ll ans = 0;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		pos[a[i]] = i;
		ans += query(1, i - 1, a[i], 0);
		for(int j = i; j <= n; j += lowbit(j))
			insert(rt[j], 1, n, a[i], 1);
	}
	printf("%lld\n", ans);
	for(int i = 1; i < m; i++)
	{
		int x;
		scanf("%d", &x);
		ans -= query(1, pos[x] - 1, x, 0);
		ans -= query(pos[x] + 1, n, x, 1);
		printf("%lld\n", ans);
		for(int j = pos[x]; j <= n; j += lowbit(j))
			insert(rt[j], 1, n, x, -1);
	}
	return 0;
}
