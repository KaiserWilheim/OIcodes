#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(i) ((i)&-(i))
const int N = 100010, M = 1000010;
int n, m;
int S;
int a[N];
int bl[N];
struct Query
{
	int l, r, a, b, id;
	bool operator < (const Query &rhs)const
	{
		return bl[l] == bl[rhs.l] ? r < rhs.r : l < rhs.l;
	}
};
Query q[M];
int ans[M];
int cnt[N], scnt[N];
void add(int x)
{
	cnt[a[x]]++;
	if(cnt[a[x]] == 1)scnt[bl[a[x]]]++;
}
void del(int x)
{
	cnt[a[x]]--;
	if(cnt[a[x]] == 0)scnt[bl[a[x]]]--;
}
int sum(int l, int r)
{
	int res = 0;
	if(bl[l] == bl[r])
	{
		for(int i = l; i <= r; i++)
			res += (cnt[i] > 0);
		return res;
	}
	for(int i = l; i <= bl[l] * S; i++)res += (cnt[i] > 0);
	for(int i = bl[l] + 1; i < bl[r]; i++)res += scnt[i];
	for(int i = (bl[r] - 1) * S + 1; i <= r; i++)res += (cnt[i] > 0);
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	S = sqrt(n) + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		bl[i] = (i - 1) / S + 1;
	}
	for(int i = 1; i <= m; i++)
	{
		int l, r, a, b;
		scanf("%d%d%d%d", &l, &r, &a, &b);
		q[i] = { l,r,a,b,i };
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
		while(l > q[i].l)add(--l);
		while(r < q[i].r)add(++r);
		while(l < q[i].l)del(l++);
		while(r > q[i].r)del(r--);
		ans[q[i].id] = sum(q[i].a, q[i].b);
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
