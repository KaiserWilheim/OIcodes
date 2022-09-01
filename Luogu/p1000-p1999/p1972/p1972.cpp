#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int a[N];
int tr[N];
int pre[N];
int ans[N];
struct Query
{
	int l, r;
	int id;
	bool operator < (const Query &a) const
	{
		return r == a.r ? l < a.l : r < a.r;
	}
}q[N];
int lowbit(int x) { return x & -x; }
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + 1 + m);
	int pos = 1;
	for(int i = 1; i <= n; i++)
	{
		if(pre[a[i]] != 0)add(pre[a[i]], -1);
		add(i, 1);
		pre[a[i]] = i;
		while(q[pos].r == i && pos <= m)
		{
			ans[q[pos].id] = sum(q[pos].r) - sum(q[pos].l - 1);
			pos++;
		}
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}