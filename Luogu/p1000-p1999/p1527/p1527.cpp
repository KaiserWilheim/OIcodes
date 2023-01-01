#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = 1000010;
#define lowbit(i) ((i)&-(i))
int n, m;
struct Query
{
	int l, t, r, b, k, id;
};
Query q[N + M], q1[N + M], q2[N + M];
int tot;
int tr[N][N];
int ans[M];
void add(int x, int y, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		for(int j = y; j <= n; j += lowbit(j))
			tr[i][j] += c;
}
int sum(int x, int y)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		for(int j = y; j; j -= lowbit(j))
			res += tr[i][j];
	return res;
}
void solve(int ql, int qr, int l, int r)
{
	if(ql > qr)return;
	if(l == r)
	{
		for(int i = ql; i <= qr; i++)
			if(q[i].id != 0)ans[q[i].id] = l;
		return;
	}
	int tt1 = 0, tt2 = 0;
	int mid = (l + r) >> 1;
	for(int i = ql; i <= qr; i++)
	{
		if(q[i].id == 0)
		{
			if(q[i].k <= mid)
			{
				add(q[i].l, q[i].t, 1);
				q1[++tt1] = q[i];
			}
			else
			{
				q2[++tt2] = q[i];
			}
		}
		else
		{
			int tmp = sum(q[i].r, q[i].b) - sum(q[i].l - 1, q[i].b) - sum(q[i].r, q[i].t - 1) + sum(q[i].l - 1, q[i].t - 1);
			if(tmp >= q[i].k)
			{
				q1[++tt1] = q[i];
			}
			else
			{
				q[i].k -= tmp;
				q2[++tt2] = q[i];
			}
		}
	}
	for(int i = 1; i <= tt1; i++)q[ql + i - 1] = q1[i];
	for(int i = 1; i <= tt2; i++)q[ql + tt1 + i - 1] = q2[i];
	for(int i = ql; i <= ql + tt1 - 1; i++)
		if(q[i].id == 0 && q[i].k <= mid)add(q[i].l, q[i].t, -1);
	solve(ql, ql + tt1 - 1, l, mid);
	solve(ql + tt1, qr, mid + 1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int x;
			scanf("%d", &x);
			q[++tot] = { i,j,0,0,x,0 };
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int l, r, t, b, k;
		scanf("%d%d%d%d%d", &l, &t, &r, &b, &k);
		q[++tot] = { l,t,r,b,k,i };
	}
	solve(1, tot, INT_MIN, INT_MAX);
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
